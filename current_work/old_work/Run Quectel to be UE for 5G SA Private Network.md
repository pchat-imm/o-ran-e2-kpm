## Run Quectel to be UE for 5G SA Private Network
recommended from https://github.com/srsran/srsRAN_Project/discussions/426

connect uhd devices and check if it present
```
>> uhd_find_devices 
[INFO] [UHD] linux; GNU C++ version 10.5.0; Boost_107400; UHD_4.0.0.HEAD-0-g90ce6062
[INFO] [B200] Loading firmware image: /usr/local/share/uhd/images/usrp_b200_fw.hex...
--------------------------------------------------
-- UHD Device 0
--------------------------------------------------
Device Address:
    serial: 326C096
    name: MyB210
    product: B210
    type: b200
```
using mmcli (ModemManager CLI) to setup connection
```
>> sudo mmcli -L
    /org/freedesktop/ModemManager1/Modem/2 [Quectel] RM510Q-GL

>> sudo mmcli -m 2 -e
successfully enabled the modem

>> sudo mmcli -m 2 --simple-connect="apn=srsapn"
successfully connected the modem
```
with `enable` the status of mmcli will show `registered`, and with `simple-connect` successfully it will show `connected` with green color

bring the interface up and lease an IP address to the client from the DHCP server using `udhcpc` (micro Dynamic Host Configuration Protocol Client (uDHCPC))
```
sudo ip link set wwan0 up

sudo udhcpc -q -f -i wwan0
	udhcpc: started, v1.30.1
	udhcpc: sending discover
	udhcpc: sending select for 10.38.223.119
	udhcpc: lease of 10.38.223.119 obtained, lease time 7200
```
q = quit after obtaining a lease

check the assigned IP address
```
ifconfig wwan0
```
go to minicom to config the quectel
```
sudo minicom -s
```
setting serial port </br>
<img src="https://github.com/pchat-imm/quectel_rm510q_gl/assets/40858099/eff7a2fd-395d-41b7-8725-8a9177d57f36" width="30%" height="30%"/> <br/>
make sure </br>
> - serial device = /dev/ttyUSB2 \
> - bps = 115200 (default) \
> - Hardware flow control = No \

where each ttyUSB is, so we choose `ttyUSB2`
> - /dev/ttyUSB0 - DM 
> - /dev/ttyUSB1 - For GPS NMEA message output 
> - /dev/ttyUSB2 - For AT command communication 
> - /dev/ttyUSB3 - For PPP (Point-to-Point) connection or AT command communication 

<img src="https://github.com/pchat-imm/quectel_rm510q_gl/assets/40858099/a289b780-4135-44cd-a02e-da1e2a03187a" width=50% height=50%/> <br/>
everytime finish `Save setup as dfl` before `exit`


basic minicom menu
- using ctrl A + E = echo ON, to show what you type on the screen
- usign ctrl A + C = clear screen
- using ctrl A + X to quit the minicom
- if minicom freeze, open another window and try
```
>> ps aux | grep minicom
>> sudo kill -SIGTERM <PID>
```
from B. Agarwal, C. Felber, N. Pandeya, F. Kaltenberger, M. Ruffini and G. -M. Muntean, "Analysis of Real-Time Video Streaming and Throughput Performance Using the Open Air Interface Stack on Multiple UEs," 2023 IEEE Conference on Standards for Communications and Networking (CSCN), Munich, Germany, 2023, pp. 235-240, doi: 10.1109/CSCN60443.2023.10453217.
```
## check if the device is connected
AT
OK

## Unlock the Quectel module (QMBN = Qualcom Modem Configuration Binary)
AT+QMBNCFG="select","Row_commercial"

## Unplug and Replug, to reboot the module
## Unplug and Replug

## see 5G band that are configured
AT+QNWPREFCFG="nr5g_band"

## set the mode to 5G SA
AT+QNWPREFCFG="mode_pref",nr5g

## Enable the 5G operation
AT+QNWPREFCFG="nr5g_disable_mode",0

## Specify the PDP context, including APN and only IPv4
AT+CGDCONT=1,"IP","internet"

## remove existing option
AT+CGDCONT=2
AT+CGDCONT=3
AT+CGDCONT?

## check the current network operator that we connect to
AT+COPS?
+COPS: 0,0,"Open5GS Magic",11

## enable roaming 
AT+QNWPREFCFG="roam_pref",255
```


- [ ] set network mode to `SA/NSA`
AT+QNWPREFCFG="mode_pref",LTE:NR5G

- [ ] config `APN` to match APN in subscriber_list -> then check APN information
AT+CGDCONT=1,"IP","internet"
AT+CGDCONT=2
AT+CGDCONT=3

- [ ] enable `roaming`
AT+QNWPREFCFG="roam_pref".255

- [ ] toggle `NAT` rule again, so that the UE can connect to internet
other things to try
- [ ] disable VoLTE and/or VoNR

another method
https://open-cells.com/index.php/2022/07/26/ues/

possible issue with modemManager with QMI command
from: https://medium.com/slice-of-pi-innovations-hacks/setting-up-a-data-connection-via-qmi-interface-on-raspberry-pi-with-quectel-modem-and-sixfab-shield-aa2b2b3f3d5c

IP passthrough
- explanation of IP passthrough from https://github.com/natecarlson/quectel-rgmii-configuration-notes
- example of IP passthrough from https://chestertechrepairs.com/blogs/news/ninja-at-commands-over-telnet-192-168-225-1-5000
- rgmii config https://github.com/natecarlson/quectel-rgmii-configuration-notes
- IPPT to NAT 
	- https://forums.quectel.com/t/cant-place-rm520-in-ip-passthrough-ippt-mode/21928/4
	- https://wirelessjoint.com/viewtopic.php?t=4023