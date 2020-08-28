#Summary

A combination of Arduino sketch and Applescript that makes a push-to-talk button for Microsoft Teams. The script can be configured to send the Mute Toggle hotkey directly or send a custom hotkey that can trigger the AppleScript, or something like an AutoHotkey script for Windows users.

#Hardware

- Arduino or clone that can support native USB HID output (Leonardo, Sparkfun Pro Micro, etc.)
- Button of some sort, one leg to GND, the second to the digital pin of choice (default: Arduino pin 2)

#AppleScript Automator Setup

If you want to use PTT when Teams is out of focus you will need to utilize some AppleScript combined with Automater.

1. Open *Automator*
2. Click *File* -> *New*
3. Select *Quick Action*
4. *Set Workflow receives current* to "*no input*" in "*any application*"
5. From the *Library section* in the left pane select "*Utilities*", then "*Run AppleScript*"
6. Copy and paste the contents of the AppleScript included in this repository into the AppleScript window, click the :arrow_forward: button if you want to test it
7. Click *File* -> *Save* and give the Automator task a name that's easy to remember, like "Teams PTT Script"
8. Close Automator, open *System Preferences* -> *Keyboard*
9. Click the *Shortcuts* tab, select the *Services section* in the left pane, scroll the right pane until you find your Automator service (usually in the General section)
10. Click the to the right of your service, when it's ready to accept input press your Teams PTT button

#TODO

- Create AutoHotkey script and instructions for Windows users
- Add LED control
- Add additional buttons to control more Teams functions
- Write support for a Bluetooth HID hardware