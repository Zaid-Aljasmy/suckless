#!/bin/sh
#
# # set environment variables for X
# export DISPLAY=:0
# export XAUTHORITY="$HOME/.Xauthority"
#
# # start conky with custom config
# # conky -c ~/.config/conky/conkyrc &
#
# # start redshift
# redshift -P -O 5500 &
#
# # start dunst
# dunst &
#
# # set brightness
# brightnessctl set 30% &
#
# # disable bell sound
# xset -b &
#
# # set mouse speed
# xinput --set-prop 10 "libinput Accel Speed" 1 &
#
# # keyboard repeat rate
# xset r rate 200 40 &
#
# # start picom compositor
# # picom &
#
# # restore wallpaper
# nitrogen --restore &
#
# # start slstatus
# slstatus &
#
# finally start DWM
exec dwm

