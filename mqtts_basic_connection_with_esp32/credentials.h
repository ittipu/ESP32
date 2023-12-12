const char* ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFYDCCBEigAwIBAgIQQAF3ITfU6UK47naqPGQKtzANBgkqhkiG9w0BAQsFADA/
MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT
DkRTVCBSb290IENBIFgzMB4XDTIxMDEyMDE5MTQwM1oXDTI0MDkzMDE4MTQwM1ow
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwggIiMA0GCSqGSIb3DQEB
AQUAA4ICDwAwggIKAoICAQCt6CRz9BQ385ueK1coHIe+3LffOJCMbjzmV6B493XC
ov71am72AE8o295ohmxEk7axY/0UEmu/H9LqMZshftEzPLpI9d1537O4/xLxIZpL
wYqGcWlKZmZsj348cL+tKSIG8+TA5oCu4kuPt5l+lAOf00eXfJlII1PoOK5PCm+D
LtFJV4yAdLbaL9A4jXsDcCEbdfIwPPqPrt3aY6vrFk/CjhFLfs8L6P+1dy70sntK
4EwSJQxwjQMpoOFTJOwT2e4ZvxCzSow/iaNhUd6shweU9GNx7C7ib1uYgeGJXDR5
bHbvO5BieebbpJovJsXQEOEO3tkQjhb7t/eo98flAgeYjzYIlefiN5YNNnWe+w5y
sR2bvAP5SQXYgd0FtCrWQemsAXaVCg/Y39W9Eh81LygXbNKYwagJZHduRze6zqxZ
Xmidf3LWicUGQSk+WT7dJvUkyRGnWqNMQB9GoZm1pzpRboY7nn1ypxIFeFntPlF4
FQsDj43QLwWyPntKHEtzBRL8xurgUBN8Q5N0s8p0544fAQjQMNRbcTa0B7rBMDBc
SLeCO5imfWCKoqMpgsy6vYMEG6KDA0Gh1gXxG8K28Kh8hjtGqEgqiNx2mna/H2ql
PRmP6zjzZN7IKw0KKP/32+IVQtQi0Cdd4Xn+GOdwiK1O5tmLOsbdJ1Fu/7xk9TND
TwIDAQABo4IBRjCCAUIwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYw
SwYIKwYBBQUHAQEEPzA9MDsGCCsGAQUFBzAChi9odHRwOi8vYXBwcy5pZGVudHJ1
c3QuY29tL3Jvb3RzL2RzdHJvb3RjYXgzLnA3YzAfBgNVHSMEGDAWgBTEp7Gkeyxx
+tvhS5B1/8QVYIWJEDBUBgNVHSAETTBLMAgGBmeBDAECATA/BgsrBgEEAYLfEwEB
ATAwMC4GCCsGAQUFBwIBFiJodHRwOi8vY3BzLnJvb3QteDEubGV0c2VuY3J5cHQu
b3JnMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9jcmwuaWRlbnRydXN0LmNvbS9E
U1RST09UQ0FYM0NSTC5jcmwwHQYDVR0OBBYEFHm0WeZ7tuXkAXOACIjIGlj26Ztu
MA0GCSqGSIb3DQEBCwUAA4IBAQAKcwBslm7/DlLQrt2M51oGrS+o44+/yQoDFVDC
5WxCu2+b9LRPwkSICHXM6webFGJueN7sJ7o5XPWioW5WlHAQU7G75K/QosMrAdSW
9MUgNTP52GE24HGNtLi1qoJFlcDyqSMo59ahy2cI2qBDLKobkx/J3vWraV0T9VuG
WCLKTVXkcGdtwlfFRjlBz4pYg1htmf5X6DYO8A4jqv2Il9DjXA6USbW1FzXSLr9O
he8Y4IWS6wY7bCkjCWDcRQJMEhg76fsO3txE+FiYruq9RUWhiF1myv4Q6W+CyBFC
Dfvp7OOGAN6dEOM4+qR9sdjoSYKEBpsr6GtPAQw4dy753ec5
-----END CERTIFICATE-----

)EOF";

const char* client_certificate = R"KEY(
  -----BEGIN CERTIFICATE-----
MIIEGjCCAwKgAwIBAgISA6tca4UlZyCciaYIMOEpuY/8MA0GCSqGSIb3DQEBCwUA
MDIxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQswCQYDVQQD
EwJSMzAeFw0yMzEyMTAwNTM1NTJaFw0yNDAzMDkwNTM1NTFaMBcxFTATBgNVBAMT
DGlvdGNyYWNrLmNvbTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABJLnNSyzmR12
USanmAean53mDyeS8CSakmFkPYkm6uVD84hV6ywKevjGulpXUmgiCAD7VFvaeMba
Dy+Eu7HI8wWjggIOMIICCjAOBgNVHQ8BAf8EBAMCB4AwHQYDVR0lBBYwFAYIKwYB
BQUHAwEGCCsGAQUFBwMCMAwGA1UdEwEB/wQCMAAwHQYDVR0OBBYEFAgZQa4gjHyN
aLmdTJU2K5d3cCy8MB8GA1UdIwQYMBaAFBQusxe3WFbLrlAJQOYfr52LFMLGMFUG
CCsGAQUFBwEBBEkwRzAhBggrBgEFBQcwAYYVaHR0cDovL3IzLm8ubGVuY3Iub3Jn
MCIGCCsGAQUFBzAChhZodHRwOi8vcjMuaS5sZW5jci5vcmcvMBcGA1UdEQQQMA6C
DGlvdGNyYWNrLmNvbTATBgNVHSAEDDAKMAgGBmeBDAECATCCAQQGCisGAQQB1nkC
BAIEgfUEgfIA8AB2ADtTd3U+LbmAToswWwb+QDtn2E/D9Me9AA0tcm/h+tQXAAAB
jFJwe9cAAAQDAEcwRQIhAJlV3mGS/fNd7Le0Ogihbd0Om6x0ueNnMi01YMTprt2P
AiAmYbxERTV8maF17oMwGroPz+09HxiohJUcMUtgOVkizgB2AEiw42vapkc0D+Vq
AvqdMOscUgHLVt0sgdm7v6s52IRzAAABjFJwe9YAAAQDAEcwRQIgH8n8N/STU/1G
yHLUtx4Xm3/HedANGvI3y5C/B39ptaUCIQCfmrfA4gEXZVSr5DkvR/gZZ96QiBY1
eyFh42qbhrlpnzANBgkqhkiG9w0BAQsFAAOCAQEAgYVd5y+FebGiTE9U3jt+Koo1
T+3po1rchbHw/FvWLtXM55aHkaEZyHyQGBkifg+mDw/jRw+a0P12mr6AQyz3/f3E
OL5Tyibvv5ZCmNouX/dsWpLu2Y/ZLN8yqat7sZCZq5lVO98H9CCVBw45tsB0GT9v
g+qBkAj9X4QtSyzChzUW4FIeodDqa6A51qDzg2a1/0CA2MMtgsP7LsdiKEOvrvef
wQ/2W+5QGWFs4aGlsrZAtSxZsDyQ6yfPbaXD++7Ib/K6XFYs+hMFa2OTajzl/QIs
29Q7O4wuUs71YJqqalg0OzdYSJhsE8rRdEyg1HoSI8lhPRbJMMPGYeiga8Wb9w==
-----END CERTIFICATE-----
)KEY";

const char* private_key = R"KEY(
  -----BEGIN PRIVATE KEY-----
MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgmh9LsKzJWFvC8k6v
2sqL8YJiCsxGnkj/ysUtx7ehewWhRANCAASS5zUss5kddlEmp5gHmp+d5g8nkvAk
mpJhZD2JJurlQ/OIVessCnr4xrpaV1JoIggA+1Rb2njG2g8vhLuxyPMF
-----END PRIVATE KEY-----
)KEY";