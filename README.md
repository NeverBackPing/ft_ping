# ft_ping

![protocole](/asset/img/protocole.png)

Schéma: [Packet formats](https://homepages.uc.edu/~thomam/Net1\/Packet_Formats)



![protocole](/asset/img/socket.png)


```bash
                Message ICMP
┌────────────────────────────────────────────────┐
│               En-tête ICMP                     │
├─────────┬─────────┬──────────┬────────┬────────┤
│ Type    │ Code    │ Checksum │ ID     │ Seq    │
│ 1 octet │ 1 octet │ 2 octets │2 octets│2 octets│
├─────────┴─────────┴──────────┴────────┴────────┤
│                Payload (Message)               │
│        "Hello", "ABCDEFGH", etc.               │
└────────────────────────────────────────────────┘
```

![protocole](/asset/img/socket_client_server.png)

type: [type message](https://www.geeksforgeeks.org/computer-networks/internet-control-message-protocol-icmp/)
