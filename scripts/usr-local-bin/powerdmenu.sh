#!/bin/sh

# export DISPLAY=:0
# export XAUTHORITY="/home/zaid/.Xauthority"
# export DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/$(id -u)/bus"

confirm() {
    printf "Yes\nNo\n" | dmenu -i -p "Are you sure?" | grep -iq "^yes"
}

choice=$(printf "Shutdown\nReboot\nSuspend\nLogout\n" | dmenu -i -p "Power Menu:")

case "$choice" in
  Shutdown)
    confirm && sudo poweroff
    ;;
  Reboot)
    confirm && sudo reboot
    ;;
  Suspend)
    confirm && sudo zzz
    ;;
  Logout)
    confirm && pkill -KILL -u "$USER"
    ;;
esac


# to make this script work you need to add this command by type it in your terminal: (dont missing replace the zaid with your username!!)

#echo "zaid ALL=(ALL) NOPASSWD: /sbin/poweroff, /sbin/reboot, /usr/sbin/zzz" | sudo EDITOR='tee -a' visudo

# this command for make the three commands " poweroff , reboot, zzz," running without the passowrd sudo.
