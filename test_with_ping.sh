#!/bin/bash

# ============================================================
#                   ft_ping TEST SUITE
#
#   Compare:
#       system ping
#       ./ft_ping
#
#   Checks:
#       - Behavior
#       - Crash
#       - Memory leaks
#       - Memory errors
#       - File descriptors
#
#   Usage:
#       sudo ./test_with_ping.sh
# ============================================================


# ============================================================
#                         CONFIGURATION
# ============================================================

PROGRAM="./ft_ping"

TIMEOUT=11

PING_OUTPUT="/tmp/ft_ping_test_ping_output"
FT_OUTPUT="/tmp/ft_ping_test_ft_output"
VALGRIND_OUTPUT="/tmp/ft_ping_test_valgrind"


# ============================================================
#                           COLORS
# ============================================================

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'

BOLD='\033[1m'
RESET='\033[0m'


# ============================================================
#                          COUNTERS
# ============================================================

PASS=0
FAIL=0

MEM_PASS=0
MEM_FAIL=0

FD_PASS=0
FD_FAIL=0

ERROR_PASS=0
ERROR_FAIL=0

TEST_NUMBER=0


# ============================================================
#                    FAILURE STORAGE
# ============================================================

FAIL_INPUTS=()
FAIL_REASONS=()

MEM_FAIL_INPUTS=()
MEM_FAIL_REASONS=()

FD_FAIL_INPUTS=()
FD_FAIL_REASONS=()

ERROR_FAIL_INPUTS=()
ERROR_FAIL_REASONS=()


# ============================================================
#                       CHECK SUDO
# ============================================================

if [ "$EUID" -ne 0 ]; then
    echo
    echo -e "${RED}${BOLD}ERROR:${RESET} This test suite must be run with sudo."
    echo
    echo "Usage:"
    echo "    sudo ./test_with_ping.sh"
    echo
    exit 1
fi


# ============================================================
#                    CHECK FT_PING
# ============================================================

if [ ! -x "$PROGRAM" ]; then

    echo
    echo -e "${RED}${BOLD}ERROR:${RESET} $PROGRAM does not exist or is not executable."
    echo
    echo "Compile your program first:"
    echo
    echo "    make"
    echo

    exit 1
fi


# ============================================================
#                     CHECK PING
# ============================================================

if ! command -v ping >/dev/null 2>&1; then

    echo
    echo -e "${RED}${BOLD}ERROR:${RESET} system ping was not found."
    echo

    exit 1
fi


# ============================================================
#                   CHECK VALGRIND
# ============================================================

if ! command -v valgrind >/dev/null 2>&1; then

    echo
    echo -e "${RED}${BOLD}ERROR:${RESET} valgrind was not found."
    echo
    echo "Install it with:"
    echo
    echo "    sudo apt install valgrind"
    echo

    exit 1
fi


# ============================================================
#                        FUNCTIONS
# ============================================================


# ------------------------------------------------------------
# Print section
# ------------------------------------------------------------

print_section()
{
    local title="$1"

    echo
    echo
    echo -e "${CYAN}${BOLD}============================================================${RESET}"
    echo -e "${CYAN}${BOLD}                    $title${RESET}"
    echo -e "${CYAN}${BOLD}============================================================${RESET}"
    echo
}


# ------------------------------------------------------------
# Print separator
# ------------------------------------------------------------

print_separator()
{
    echo -e "${CYAN}------------------------------------------------------------${RESET}"
}


# ------------------------------------------------------------
# Determine behavior from timeout return code
# ------------------------------------------------------------

get_behavior()
{
    local ret="$1"

    if [ "$ret" -eq 124 ]; then
        echo "RUNNING"
    else
        echo "STOPPED"
    fi
}


# ------------------------------------------------------------
# Run system ping
# ------------------------------------------------------------

run_ping()
{
    local input="$1"

    timeout "$TIMEOUT" \
        ping "$input" \
        > "$PING_OUTPUT" 2>&1

    return $?
}


# ------------------------------------------------------------
# Run ft_ping
# ------------------------------------------------------------

run_ft_ping()
{
    local input="$1"

    timeout "$TIMEOUT" \
        "$PROGRAM" "$input" \
        > "$FT_OUTPUT" 2>&1

    return $?
}


# ============================================================
#                    BEHAVIOR TEST
# ============================================================

test_input()
{
    local input="$1"
    local category="$2"

    TEST_NUMBER=$((TEST_NUMBER + 1))

    echo
    print_separator

    echo -e "${BOLD}${WHITE}[TEST $TEST_NUMBER]${RESET}"
    echo -e "${WHITE}Category :${RESET} ${BLUE}$category${RESET}"
    echo -e "${WHITE}Input    :${RESET} ${YELLOW}$input${RESET}"

    print_separator

    # --------------------------------------------------------
    # Run real ping
    # --------------------------------------------------------

    run_ping "$input"
    ping_ret=$?

    # --------------------------------------------------------
    # Run ft_ping
    # --------------------------------------------------------

    run_ft_ping "$input"
    ft_ret=$?

    # --------------------------------------------------------
    # Determine behavior
    # --------------------------------------------------------

    ping_behavior=$(get_behavior "$ping_ret")
    ft_behavior=$(get_behavior "$ft_ret")

    # --------------------------------------------------------
    # Detect ft_ping crash
    # --------------------------------------------------------

    ft_crash=0
    ft_signal=""

    if [ "$ft_ret" -ge 128 ] && [ "$ft_ret" -ne 124 ]; then

        ft_crash=1
        ft_signal=$((ft_ret - 128))

    fi

    # --------------------------------------------------------
    # Display
    # --------------------------------------------------------

    echo
    echo -e "    ${WHITE}ping    :${RESET} ${CYAN}$ping_behavior${RESET}"
    echo -e "    ${WHITE}ft_ping :${RESET} ${CYAN}$ft_behavior${RESET}"

    # --------------------------------------------------------
    # Compare
    # --------------------------------------------------------

    if [ "$ft_crash" -eq 1 ]; then

        echo
        echo -e "    ${RED}${BOLD}RESULT : FAIL${RESET}"
        echo -e "    ${RED}CAUSE  : ft_ping crashed with signal $ft_signal${RESET}"

        FAIL=$((FAIL + 1))

        FAIL_INPUTS+=("$input")
        FAIL_REASONS+=("ft_ping crashed with signal $ft_signal")

    elif [ "$ping_behavior" != "$ft_behavior" ]; then

        echo
        echo -e "    ${RED}${BOLD}RESULT : FAIL${RESET}"
        echo -e "    ${RED}CAUSE  : ping $ping_behavior / ft_ping $ft_behavior${RESET}"

        FAIL=$((FAIL + 1))

        FAIL_INPUTS+=("$input")
        FAIL_REASONS+=("ping $ping_behavior / ft_ping $ft_behavior")

    else

        echo
        echo -e "    ${GREEN}${BOLD}RESULT : PASS${RESET}"

        PASS=$((PASS + 1))

    fi

    # --------------------------------------------------------
    # Display output only when failed
    # --------------------------------------------------------

    if [ "$ft_crash" -eq 1 ] ||
       [ "$ping_behavior" != "$ft_behavior" ]; then

        echo

        echo -e "    ${YELLOW}--- ping output ---${RESET}"

        if [ -s "$PING_OUTPUT" ]; then
            head -n 5 "$PING_OUTPUT" | sed 's/^/        /'
        else
            echo "        <empty>"
        fi

        echo

        echo -e "    ${YELLOW}--- ft_ping output ---${RESET}"

        if [ -s "$FT_OUTPUT" ]; then
            head -n 5 "$FT_OUTPUT" | sed 's/^/        /'
        else
            echo "        <empty>"
        fi

    fi

    print_separator
}


# ============================================================
#                  VALGRIND TEST
# ============================================================

test_valgrind()
{
    local input="$1"
    local category="$2"

    echo
    print_separator

    echo -e "${BOLD}${WHITE}[VALGRIND]${RESET}"
    echo -e "${WHITE}Category :${RESET} ${BLUE}$category${RESET}"
    echo -e "${WHITE}Input    :${RESET} ${YELLOW}$input${RESET}"

    print_separator

    rm -f "$VALGRIND_OUTPUT"

    # --------------------------------------------------------
    # Run ft_ping through Valgrind
    # --------------------------------------------------------

    valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-fds=yes \
        --errors-for-leak-kinds=definite,indirect \
        --error-exitcode=42 \
        "$PROGRAM" "$input" \
        > "$VALGRIND_OUTPUT" 2>&1

    valgrind_ret=$?

    # ========================================================
    # MEMORY
    # ========================================================

    definitely_lost=$(grep \
        "definitely lost:" \
        "$VALGRIND_OUTPUT" \
        | tail -n 1)

    indirectly_lost=$(grep \
        "indirectly lost:" \
        "$VALGRIND_OUTPUT" \
        | tail -n 1)

    possibly_lost=$(grep \
        "possibly lost:" \
        "$VALGRIND_OUTPUT" \
        | tail -n 1)

    # --------------------------------------------------------
    # Check definite + indirect leaks
    # --------------------------------------------------------

    if echo "$definitely_lost" |
        grep -qE "definitely lost: 0 bytes in 0 blocks" &&
       echo "$indirectly_lost" |
        grep -qE "indirectly lost: 0 bytes in 0 blocks"; then

        echo
        echo -e "    ${GREEN}MEMORY : PASS${RESET}"

        MEM_PASS=$((MEM_PASS + 1))

    else

        echo
        echo -e "    ${RED}MEMORY : FAIL${RESET}"

        echo -e "        ${YELLOW}$definitely_lost${RESET}"
        echo -e "        ${YELLOW}$indirectly_lost${RESET}"
        echo -e "        ${YELLOW}$possibly_lost${RESET}"

        MEM_FAIL=$((MEM_FAIL + 1))

        MEM_FAIL_INPUTS+=("$input")

        MEM_FAIL_REASONS+=(
            "$definitely_lost / $indirectly_lost"
        )

    fi


    # ========================================================
    # MEMORY ERRORS
    # ========================================================

    error_summary=$(grep \
        "ERROR SUMMARY:" \
        "$VALGRIND_OUTPUT" \
        | tail -n 1)

    if echo "$error_summary" |
        grep -qE "ERROR SUMMARY: 0 errors"; then

        echo -e "    ${GREEN}ERRORS : PASS${RESET}"

        ERROR_PASS=$((ERROR_PASS + 1))

    else

        echo -e "    ${RED}ERRORS : FAIL${RESET}"
        echo -e "        ${YELLOW}$error_summary${RESET}"

        ERROR_FAIL=$((ERROR_FAIL + 1))

        ERROR_FAIL_INPUTS+=("$input")
        ERROR_FAIL_REASONS+=("$error_summary")

    fi


    # ========================================================
    # FILE DESCRIPTORS
    # ========================================================

    # Valgrind prints:
    #
    # FILE DESCRIPTORS: 3 open (3 std) at exit.
    #
    # We want exactly 3.
    #

    fd_summary=$(grep \
        "FILE DESCRIPTORS:" \
        "$VALGRIND_OUTPUT" \
        | tail -n 1)

    if echo "$fd_summary" |
        grep -qE "FILE DESCRIPTORS: 3 open \(3 std\) at exit"; then

        echo -e "    ${GREEN}FDs    : PASS${RESET}"

        FD_PASS=$((FD_PASS + 1))

    else

        echo -e "    ${RED}FDs    : FAIL${RESET}"
        echo -e "        ${YELLOW}$fd_summary${RESET}"

        FD_FAIL=$((FD_FAIL + 1))

        FD_FAIL_INPUTS+=("$input")
        FD_FAIL_REASONS+=("$fd_summary")

    fi


    # ========================================================
    # DISPLAY VALGRIND DETAILS ON FAILURE
    # ========================================================

    if [ "$MEM_FAIL" -gt 0 ] ||
       [ "$FD_FAIL" -gt 0 ] ||
       [ "$ERROR_FAIL" -gt 0 ]; then

        echo
        echo -e "    ${YELLOW}--- Valgrind details ---${RESET}"

        grep -E \
            "definitely lost:" \
            "$VALGRIND_OUTPUT" \
            | tail -n 1 \
            | sed 's/^/        /'

        grep -E \
            "indirectly lost:" \
            "$VALGRIND_OUTPUT" \
            | tail -n 1 \
            | sed 's/^/        /'

        grep -E \
            "possibly lost:" \
            "$VALGRIND_OUTPUT" \
            | tail -n 1 \
            | sed 's/^/        /'

        grep -E \
            "ERROR SUMMARY:" \
            "$VALGRIND_OUTPUT" \
            | tail -n 1 \
            | sed 's/^/        /'

        grep -E \
            "FILE DESCRIPTORS:" \
            "$VALGRIND_OUTPUT" \
            | tail -n 1 \
            | sed 's/^/        /'
    fi

    print_separator
}


# ============================================================
#                      TEST ARRAYS
# ============================================================


# ============================================================
#                         IPv4
# ============================================================

IPV4_TESTS=(

    "127.0.0.1"

    "8.8.8.8"
    "8.8.4.4"

    "1.1.1.1"
    "1.0.0.1"

    "9.9.9.9"

    "10.0.0.1"

    "172.16.0.1"

    "192.168.0.1"
    "192.168.1.1"
)


# ============================================================
#                       HOSTNAMES
# ============================================================

HOSTNAME_TESTS=(

    "localhost"

    "google.com"
    "www.google.com"

    "github.com"
    "www.github.com"

    "example.com"

    "cloudflare.com"
    "www.cloudflare.com"

    "youtube.com"

    "wikipedia.org"

    "mail.google.com"

    "api.github.com"

    "www.google.co.uk"

    "www.amazon.fr"

    "www.wikipedia.org"
)


# ============================================================
#                      REVERSE DNS
# ============================================================

REVERSE_DNS_TESTS=(

    "8.8.8.8"
    "8.8.4.4"

    "1.1.1.1"
    "1.0.0.1"

    "9.9.9.9"
)


# ============================================================
#                     SPECIAL INPUTS
# ============================================================

SPECIAL_TESTS=(

    "1"
    "1.2"
    "1.2.3"

    "0.0.0.0"
    "255.255.255.255"
)


# ============================================================
#                    INVALID INPUTS
# ============================================================

INVALID_TESTS=(

    # --------------------------------------------------------
    # Invalid IPv4
    # --------------------------------------------------------

    "256.256.256.256"
    "999.999.999.999"

    "300.1.1.1"
    "1.300.1.1"
    "1.1.300.1"
    "1.1.1.300"

    # --------------------------------------------------------
    # Invalid IPv4 syntax
    # --------------------------------------------------------

    ".1.2.3"
    "1.2.3."

    "1..2.3"
    "1.2..3"

    "1.2.3..4"
    "1...2.3"

    # --------------------------------------------------------
    # Invalid hostname
    # --------------------------------------------------------

    "invalid.invalid"

    "does-not-exist.local"

    "this-host-does-not-exist-123456789.com"

    # --------------------------------------------------------
    # Malformed hostname
    # --------------------------------------------------------

    "-google.com"
    "google-.com"

    ".google.com"
    "google..com"

    "..google.com"

    # --------------------------------------------------------
    # Spaces
    # --------------------------------------------------------

    " "
    "  "

    "google com"

    "google.com "
    " google.com"

    "127.0.0.1 "
    " 127.0.0.1"

    # --------------------------------------------------------
    # Special characters
    # --------------------------------------------------------

    "!"
    "@"
    "#"
    "\$"
    "%"
    "^"
    "&"
    "*"

    "()"
    "[]"
    "{}"

    ";"
    ","

    # --------------------------------------------------------
    # URL
    # --------------------------------------------------------

    "http://google.com"
    "https://google.com"

    "www.google.com/index.html"

    # --------------------------------------------------------
    # IPv6
    # --------------------------------------------------------

    "::1"

    "2001:4860:4860::8888"
)


# ============================================================
#               VALGRIND TESTS
#
# Only inputs expected to terminate.
# ============================================================

VALGRIND_TESTS=(

    "invalid.invalid"

    "256.256.256.256"

    "999.999.999.999"

    ".1.2.3"

    "1..2.3"

    "google com"

    "!"

    "@"

    "#"

    "http://google.com"

    "::1"
)


# ============================================================
#                         HEADER
# ============================================================

clear

echo
echo -e "${CYAN}${BOLD}============================================================${RESET}"
echo -e "${CYAN}${BOLD}                  ft_ping TEST SUITE                       ${RESET}"
echo -e "${CYAN}${BOLD}============================================================${RESET}"
echo
echo -e "${WHITE}Reference :${RESET} ${BOLD}ping${RESET}"
echo -e "${WHITE}Program   :${RESET} ${BOLD}$PROGRAM${RESET}"
echo -e "${WHITE}Timeout   :${RESET} ${BOLD}${TIMEOUT}s${RESET}"
echo -e "${WHITE}Valgrind  :${RESET} ${BOLD}enabled${RESET}"
echo


# ============================================================
#                       1. IPv4
# ============================================================

print_section "1. IPv4 TESTS"

for input in "${IPV4_TESTS[@]}"; do

    test_input "$input" "IPv4"

done


# ============================================================
#                       2. HOSTNAMES
# ============================================================

print_section "2. HOSTNAME / DNS TESTS"

for input in "${HOSTNAME_TESTS[@]}"; do

    test_input "$input" "Hostname / DNS"

done


# ============================================================
#                       3. REVERSE DNS
# ============================================================

print_section "3. REVERSE DNS TESTS"

for input in "${REVERSE_DNS_TESTS[@]}"; do

    test_input "$input" "Reverse DNS"

done


# ============================================================
#                       4. SPECIAL
# ============================================================

print_section "4. SPECIAL INPUT TESTS"

for input in "${SPECIAL_TESTS[@]}"; do

    test_input "$input" "Special input"

done


# ============================================================
#                       5. INVALID
# ============================================================

print_section "5. INVALID INPUT TESTS"

for input in "${INVALID_TESTS[@]}"; do

    test_input "$input" "Invalid input"

done


# ============================================================
#                       6. VALGRIND
# ============================================================

print_section "6. MEMORY / FD / ERROR TESTS"

for input in "${VALGRIND_TESTS[@]}"; do

    test_valgrind "$input" "Valgrind"

done


# ============================================================
#                     FINAL SUMMARY
# ============================================================

echo
echo
echo -e "${CYAN}${BOLD}============================================================${RESET}"
echo -e "${CYAN}${BOLD}                       FINAL SUMMARY                        ${RESET}"
echo -e "${CYAN}${BOLD}============================================================${RESET}"


# ============================================================
#                    BEHAVIOR SUMMARY
# ============================================================

echo
echo -e "${WHITE}${BOLD}Behavior comparison${RESET}"

echo -e "    ${GREEN}PASS : $PASS${RESET}"
echo -e "    ${RED}FAIL : $FAIL${RESET}"

TOTAL_BEHAVIOR=$((PASS + FAIL))

echo -e "    TOTAL: $TOTAL_BEHAVIOR"


# ============================================================
#                    MEMORY SUMMARY
# ============================================================

echo
echo -e "${WHITE}${BOLD}Memory${RESET}"

echo -e "    ${GREEN}PASS : $MEM_PASS${RESET}"
echo -e "    ${RED}FAIL : $MEM_FAIL${RESET}"

TOTAL_MEMORY=$((MEM_PASS + MEM_FAIL))

echo -e "    TOTAL: $TOTAL_MEMORY"


# ============================================================
#                    ERROR SUMMARY
# ============================================================

echo
echo -e "${WHITE}${BOLD}Memory errors${RESET}"

echo -e "    ${GREEN}PASS : $ERROR_PASS${RESET}"
echo -e "    ${RED}FAIL : $ERROR_FAIL${RESET}"

TOTAL_ERRORS=$((ERROR_PASS + ERROR_FAIL))

echo -e "    TOTAL: $TOTAL_ERRORS"


# ============================================================
#                      FD SUMMARY
# ============================================================

echo
echo -e "${WHITE}${BOLD}File descriptors${RESET}"

echo -e "    ${GREEN}PASS : $FD_PASS${RESET}"
echo -e "    ${RED}FAIL : $FD_FAIL${RESET}"

TOTAL_FDS=$((FD_PASS + FD_FAIL))

echo -e "    TOTAL: $TOTAL_FDS"


# ============================================================
#                  BEHAVIOR FAILURES
# ============================================================

echo
echo
echo -e "${RED}${BOLD}============================================================${RESET}"
echo -e "${RED}${BOLD}                   BEHAVIOR FAILURES                       ${RESET}"
echo -e "${RED}${BOLD}============================================================${RESET}"

if [ "$FAIL" -eq 0 ]; then

    echo
    echo -e "${GREEN}${BOLD}    ✓ No behavior failure${RESET}"

else

    echo

    for ((i=0; i<FAIL; i++)); do

        echo -e "${RED}[FAIL $((i + 1))]${RESET} ${YELLOW}${FAIL_INPUTS[$i]}${RESET}"
        echo -e "    Cause : ${RED}${FAIL_REASONS[$i]}${RESET}"
        echo

    done

fi


# ============================================================
#                    MEMORY FAILURES
# ============================================================

echo
echo -e "${MAGENTA}${BOLD}============================================================${RESET}"
echo -e "${MAGENTA}${BOLD}                    MEMORY FAILURES                         ${RESET}"
echo -e "${MAGENTA}${BOLD}============================================================${RESET}"

if [ "$MEM_FAIL" -eq 0 ]; then

    echo
    echo -e "${GREEN}${BOLD}    ✓ No memory leak detected${RESET}"

else

    echo

    for ((i=0; i<MEM_FAIL; i++)); do

        echo -e "${RED}[MEMORY $((i + 1))]${RESET} ${YELLOW}${MEM_FAIL_INPUTS[$i]}${RESET}"
        echo -e "    Cause : ${RED}${MEM_FAIL_REASONS[$i]}${RESET}"
        echo

    done

fi


# ============================================================
#                   MEMORY ERROR FAILURES
# ============================================================

echo
echo -e "${RED}${BOLD}============================================================${RESET}"
echo -e "${RED}${BOLD}                   MEMORY ERROR FAILURES                    ${RESET}"
echo -e "${RED}${BOLD}============================================================${RESET}"

if [ "$ERROR_FAIL" -eq 0 ]; then

    echo
    echo -e "${GREEN}${BOLD}    ✓ No Valgrind memory errors${RESET}"

else

    echo

    for ((i=0; i<ERROR_FAIL; i++)); do

        echo -e "${RED}[ERROR $((i + 1))]${RESET} ${YELLOW}${ERROR_FAIL_INPUTS[$i]}${RESET}"
        echo -e "    Cause : ${RED}${ERROR_FAIL_REASONS[$i]}${RESET}"
        echo

    done

fi


# ============================================================
#                    FD FAILURES
# ============================================================

echo
echo -e "${BLUE}${BOLD}============================================================${RESET}"
echo -e "${BLUE}${BOLD}                  FILE DESCRIPTOR FAILURES                 ${RESET}"
echo -e "${BLUE}${BOLD}============================================================${RESET}"

if [ "$FD_FAIL" -eq 0 ]; then

    echo
    echo -e "${GREEN}${BOLD}    ✓ All file descriptors are closed${RESET}"

else

    echo

    for ((i=0; i<FD_FAIL; i++)); do

        echo -e "${RED}[FD $((i + 1))]${RESET} ${YELLOW}${FD_FAIL_INPUTS[$i]}${RESET}"
        echo -e "    Cause : ${RED}${FD_FAIL_REASONS[$i]}${RESET}"
        echo

    done

fi


# ============================================================
#                       GLOBAL RESULT
# ============================================================

echo
echo -e "${CYAN}${BOLD}============================================================${RESET}"
echo -e "${CYAN}${BOLD}                      GLOBAL RESULT                         ${RESET}"
echo -e "${CYAN}${BOLD}============================================================${RESET}"

if [ "$FAIL" -eq 0 ] &&
   [ "$MEM_FAIL" -eq 0 ] &&
   [ "$ERROR_FAIL" -eq 0 ] &&
   [ "$FD_FAIL" -eq 0 ]; then

    echo
    echo -e "${GREEN}${BOLD}                    ✓ ALL TESTS PASSED                     ${RESET}"
    echo

    RESULT=0

else

    echo
    echo -e "${RED}${BOLD}                  ✗ SOME TESTS FAILED                      ${RESET}"
    echo

    RESULT=1

fi


# ============================================================
#                         CLEANUP
# ============================================================

rm -f "$PING_OUTPUT"
rm -f "$FT_OUTPUT"
rm -f "$VALGRIND_OUTPUT"


# ============================================================
#                         EXIT
# ============================================================

exit "$RESULT"