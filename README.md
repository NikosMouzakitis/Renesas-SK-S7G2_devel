# Renesas-SK-S7G2_devel
Renesas SK-S7G2_devel


Initial content: 
Contents of this folders were extracted from E2STUDIO on Windows by building the Blinky example for
the Renesas SK-S7G2 platform and transfered on Linux OS.

run "make". Elf file will be generated in the Build folder.
```
> JLinkExe
> connect
> loadfile

J-Link>nicko@nicko:~/work/Renesas-SK-S7G2_devel/Build$ JLinkExe
SEGGER J-Link Commander V8.18 (Compiled Mar  5 2025 14:47:32)
DLL version V8.18, compiled Mar  5 2025 14:46:29

Connecting to J-Link via USB...O.K.
Firmware: J-Link OB RX621-ARM-SWD V1 compiled Mar  8 2017 13:46:30
Hardware version: V2.10
J-Link uptime (since boot): N/A (Not supported by this model)
S/N: 708001499
VTref=3.300V


Type "connect" to establish a target connection, '?' for help
J-Link>
J-Link>connect
Please specify device / core. <Default>: R7FS7G27H
Type '?' for selection dialog
Device>
Please specify target interface:
  J) JTAG (Default)
  S) SWD
  T) cJTAG
TIF>S
Specify target interface speed [kHz]. <Default>: 4000 kHz
Speed>
Device "R7FS7G27H" selected.


Connecting to target via SWD
InitTarget() start
Identifying target device...
SWD selected. Executing JTAG -> SWD switching sequence...
Initializing DAP...
DAP initialized successfully.
Low power mode detected. Waking device from low power mode.
InitTarget() end - Took 7.13ms
Found SW-DP with ID 0x5BA02477
DPv0 detected
CoreSight SoC-400 or earlier
Scanning AP map to find all available APs
AP[2]: Stopped AP scan as end of AP map has been reached
AP[0]: AHB-AP (IDR: 0x24770011, ADDR: 0x00000000)
AP[1]: APB-AP (IDR: 0x44770002, ADDR: 0x01000000)
Iterating through AP map to find AHB-AP to use
AP[0]: Core found
AP[0]: AHB-AP ROM base: 0xE00FF000
CPUID register: 0x410FC241. Implementer code: 0x41 (ARM)
Found Cortex-M4 r0p1, Little endian.
FPUnit: 6 code (BP) slots and 2 literal slots
CoreSight components:
ROMTbl[0] @ E00FF000
[0][0]: E000E000 CID B105E00D PID 000BB00C SCS-M7
[0][1]: E0001000 CID B105E00D PID 003BB002 DWT
[0][2]: E0002000 CID B105E00D PID 002BB003 FPB
[0][3]: E0000000 CID B105E00D PID 003BB001 ITM
[0][4]: E0040000 CID B105900D PID 000BB9A1 TPIU
[0][5]: E0041000 CID B105900D PID 000BB925 ETM
[0][6]: E0042000 CID B105900D PID 002BB908 CSTF
[0][7]: E0043000 CID B105900D PID 001BB961 TMC
[0][8]: E0044000 CID B105F00D PID 001BB101 TSG
Memory zones:
  Zone: "Default" Description: Default access mode
Cortex-M4 identified.
J-Link>loadfile test.elf
'loadfile': Performing implicit reset & halt of MCU.
Reset type: NORMAL (https://wiki.segger.com/J-Link_Reset_Strategies)
Reset: Halt core after reset via DEMCR.VC_CORERESET.
Reset: Reset device via AIRCR.SYSRESETREQ.
Downloading file [test.elf]...
J-Link: Flash download: Bank 0 @ 0x40120040: Skipped. Contents already match
J-Link: Flash download: Bank 1 @ 0x00000000: Skipped. Contents already match
O.K.
J-Link>r
Reset delay: 0 ms
Reset type: NORMAL (https://wiki.segger.com/J-Link_Reset_Strategies)
Reset: Halt core after reset via DEMCR.VC_CORERESET.
Reset: Reset device via AIRCR.SYSRESETREQ.
J-Link>g
Memory map 'after startup completion point' is active
```
