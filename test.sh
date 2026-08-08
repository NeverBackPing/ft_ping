#!/bin/bash

# ============================================================
#                       CONFIGURATION
# ============================================================

PROGRAM="./ft_ping"
TIMEOUT=3
OUTPUT="/tmp/ft_ping_test_output"

# ============================================================
#                         COLORS
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
#                         COUNTERS
# ============================================================

PASS=0
FAIL=0

# ============================================================
#                     CHECK PROGRAM
# ============================================================

if [ ! -x "$PROGRAM" ]; then
    echo -e "${RED}${BOLD}ERROR:${RESET} $PROGRAM does not exist or is not executable."
    echo
    echo -e "${YELLOW}Compile your program first:${RESET}"
    echo "    make"
    exit 1
fi

# ============================================================
#                    TEST VALID INPUT
# ============================================================

test_valid()
{
    local input="$1"

    printf "${WHITE}[VALID]   %-50s ${RESET}" "$input"

    timeout "$TIMEOUT" "$PROGRAM" "$input" \
        > "$OUTPUT" 2>&1

    ret=$?

    # --------------------------------------------------------
    # 124 = timeout
    #
    # Le programme tourne toujours :
    # => comportement attendu pour un input valide
    # --------------------------------------------------------

    if [ "$ret" -eq 124 ]; then
        echo -e "${GREEN}PASS${RESET} ${CYAN}(still running)${RESET}"
        PASS=$((PASS + 1))
        return
    fi

    # --------------------------------------------------------
    # 128 + signal = crash
    # --------------------------------------------------------

    if [ "$ret" -ge 128 ]; then
        signal=$((ret - 128))

        echo -e "${RED}FAIL${RESET} ${RED}(CRASH - signal $signal)${RESET}"

        echo -e "${YELLOW}        Output:${RESET}"
        head -n 5 "$OUTPUT" | sed 's/^/        /'

        FAIL=$((FAIL + 1))
        return
    fi

    # --------------------------------------------------------
    # Le programme s'est arrêté tout seul
    # --------------------------------------------------------

    echo -e "${RED}FAIL${RESET} ${RED}(stopped - exit $ret)${RESET}"

    echo -e "${YELLOW}        Output:${RESET}"
    head -n 5 "$OUTPUT" | sed 's/^/        /'

    FAIL=$((FAIL + 1))
}

# ============================================================
#                   TEST INVALID INPUT
# ============================================================

test_invalid()
{
    local input="$1"

    printf "${WHITE}[INVALID] %-50s ${RESET}" "$input"

    timeout "$TIMEOUT" "$PROGRAM" "$input" \
        > "$OUTPUT" 2>&1

    ret=$?

    # --------------------------------------------------------
    # Le programme continue :
    # => FAIL
    # --------------------------------------------------------

    if [ "$ret" -eq 124 ]; then
        echo -e "${RED}FAIL${RESET} ${RED}(still running)${RESET}"

        FAIL=$((FAIL + 1))
        return
    fi

    # --------------------------------------------------------
    # Crash
    # --------------------------------------------------------

    if [ "$ret" -ge 128 ]; then
        signal=$((ret - 128))

        echo -e "${RED}FAIL${RESET} ${RED}(CRASH - signal $signal)${RESET}"

        echo -e "${YELLOW}        Output:${RESET}"
        head -n 5 "$OUTPUT" | sed 's/^/        /'

        FAIL=$((FAIL + 1))
        return
    fi

    # --------------------------------------------------------
    # Le programme doit afficher une erreur
    #
    # On accepte :
    #
    # ft_ping...
    # Error...
    #
    # --------------------------------------------------------

    first_line=$(head -n 1 "$OUTPUT")

    if echo "$first_line" | grep -qE '^(ft_ping|Error)'; then

        echo -e "${GREEN}PASS${RESET}"

        PASS=$((PASS + 1))

    else

        echo -e "${RED}FAIL${RESET} ${RED}(unexpected output)${RESET}"

        echo -e "${YELLOW}        Output:${RESET}"
        head -n 5 "$OUTPUT" | sed 's/^/        /'

        FAIL=$((FAIL + 1))
    fi
}

# ============================================================
#                  VALID INPUTS
# ============================================================

VALID_INPUTS=(

    # ========================================================
    # LOCALHOST
    # ========================================================

    "localhost"
    "127.0.0.1"

    # ========================================================
    # HOSTNAMES CLASSIQUES
    # ========================================================

    "google.com"
    "www.google.com"
    "github.com"
    "www.github.com"
    "example.com"
    "cloudflare.com"
    "youtube.com"
    "wikipedia.org"

    # ========================================================
    # SOUS-DOMAINES
    # ========================================================

    "mail.google.com"
    "api.github.com"
    "www.cloudflare.com"

    # ========================================================
    # DOMAINES INTERNATIONAUX / SOUS-DOMAINES
    # ========================================================

    "www.google.co.uk"
    "www.amazon.fr"
    "www.wikipedia.org"

    # ========================================================
    # DNS / REVERSE DNS HOSTNAMES
    # ========================================================

    "dns.google"
    "one.one.one.one"

    # ========================================================
    # PUBLIC IPv4
    # ========================================================

    "8.8.8.8"
    "8.8.4.4"
    "1.1.1.1"
    "1.0.0.1"
    "9.9.9.9"

    # ========================================================
    # PRIVATE IPv4
    # ========================================================

    "10.0.0.1"
    "10.255.255.255"

    "172.16.0.1"
    "172.31.255.255"

    "192.168.0.1"
    "192.168.1.1"
    "192.168.255.255"

    # ========================================================
    # SPECIAL IPv4
    # ========================================================

    "0.0.0.0"
    "255.255.255.255"

    # ========================================================
    # FORMES QUE ping PEUT RESOUDRE
    #
    # IMPORTANT :
    #
    # 1
    # 1.2
    # 1.2.3
    #
    # ne sont PAS automatiquement considérés comme invalides.
    # ========================================================

    "1"
    "1.2"
    "1.2.3"
)

# ============================================================
#                  REVERSE DNS INPUTS
# ============================================================

REVERSE_DNS_INPUTS=(

    # Google DNS
    "8.8.8.8"
    "8.8.4.4"

    # Cloudflare DNS
    "1.1.1.1"
    "1.0.0.1"

    # Quad9
    "9.9.9.9"
)

# ============================================================
#                  INVALID INPUTS
# ============================================================

INVALID_INPUTS=(

    # ========================================================
    # IPv4 TROP GRANDES
    # ========================================================

    "256.256.256.256"
    "999.999.999.999"
    "300.1.1.1"
    "1.300.1.1"
    "1.1.300.1"
    "1.1.1.300"

    # ========================================================
    # IPv4 SYNTAXE CLAIREMENT INVALIDES
    # ========================================================

    ".1.2.3"
    "1.2.3."
    "1..2.3"
    "1.2..3"
    "1.2.3..4"
    "1...2.3"

    # ========================================================
    # CARACTERES INVALIDES
    # ========================================================

    "abc.def.ghi.jkl"
    "a.b.c.d"
    "1.2.3.x"
    "1.2.3.-1"
    "1.2.3.+1"
    "1.2.3.4a"

    # ========================================================
    # HOSTNAMES INEXISTANTS
    # ========================================================

    "invalid.invalid"
    "does-not-exist.local"
    "this-host-does-not-exist-123456789.com"

    # ========================================================
    # HOSTNAMES MAL FORMES
    # ========================================================

    "-google.com"
    "google-.com"
    ".google.com"
    "google..com"
    "..google.com"

    # ========================================================
    # ESPACES
    # ========================================================

    " "
    "  "
    "google com"
    "google.com "
    " google.com"
    "127.0.0.1 "
    " 127.0.0.1"

    # ========================================================
    # CARACTERES SPECIAUX
    # ========================================================

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

    # ========================================================
    # URL
    # ========================================================

    "http://google.com"
    "https://google.com"
    "www.google.com/index.html"

    # ========================================================
    # IPv6
    #
    # ft_ping = IPv4
    # ========================================================

    "::1"
    "2001:4860:4860::8888"
)

# ============================================================
#                         HEADER
# ============================================================

clear

echo
echo -e "${CYAN}${BOLD}========================================================${RESET}"
echo -e "${CYAN}${BOLD}                  ft_ping TEST SUITE                    ${RESET}"
echo -e "${CYAN}${BOLD}========================================================${RESET}"
echo
echo -e "${WHITE}Program : ${BOLD}$PROGRAM${RESET}"
echo -e "${WHITE}Timeout : ${BOLD}${TIMEOUT}s${RESET}"
echo

# ============================================================
#                    VALID HOSTNAMES / IP
# ============================================================

echo -e "${BLUE}${BOLD}========================================================${RESET}"
echo -e "${BLUE}${BOLD}                 VALID INPUTS                           ${RESET}"
echo -e "${BLUE}${BOLD}========================================================${RESET}"
echo

for input in "${VALID_INPUTS[@]}"; do
    test_valid "$input"
done

# ============================================================
#                     REVERSE DNS
# ============================================================

echo
echo -e "${CYAN}${BOLD}========================================================${RESET}"
echo -e "${CYAN}${BOLD}                 REVERSE DNS                            ${RESET}"
echo -e "${CYAN}${BOLD}========================================================${RESET}"
echo

for input in "${REVERSE_DNS_INPUTS[@]}"; do
    test_valid "$input"
done

# ============================================================
#                    INVALID INPUTS
# ============================================================

echo
echo -e "${MAGENTA}${BOLD}========================================================${RESET}"
echo -e "${MAGENTA}${BOLD}                 INVALID INPUTS                         ${RESET}"
echo -e "${MAGENTA}${BOLD}========================================================${RESET}"
echo

for input in "${INVALID_INPUTS[@]}"; do
    test_invalid "$input"
done

# ============================================================
#                       SUMMARY
# ============================================================

TOTAL=$((PASS + FAIL))

echo
echo -e "${CYAN}${BOLD}========================================================${RESET}"
echo -e "${CYAN}${BOLD}                       SUMMARY                          ${RESET}"
echo -e "${CYAN}${BOLD}========================================================${RESET}"

echo -e "  ${GREEN}${BOLD}✔ PASS : $PASS${RESET}"
echo -e "  ${RED}${BOLD}✘ FAIL : $FAIL${RESET}"
echo -e "  ${WHITE}  TOTAL: $TOTAL${RESET}"

echo -e "${CYAN}${BOLD}========================================================${RESET}"

# ============================================================
#                        RESULT
# ============================================================

if [ "$FAIL" -eq 0 ]; then

    echo
    echo -e "${GREEN}${BOLD}                 ✓ ALL TESTS PASSED                     ${RESET}"
    echo

    rm -f "$OUTPUT"
    exit 0

else

    echo
    echo -e "${RED}${BOLD}                 ✗ SOME TESTS FAILED                    ${RESET}"
    echo

    echo -e "${YELLOW}Output of the last failed test:${RESET}"
    cat "$OUTPUT"

    exit 1
fi