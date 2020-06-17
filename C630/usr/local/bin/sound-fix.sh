#!/bin/sh
## port 1
pacmd set-sink-port 1 "[Out] HeadPhones"
pactl set-sink-volume 1 +5%
sleep 1
pactl set-sink-volume 1 -5%
pacmd set-sink-port 1 "[Out] Speakers"
## port 0
pacmd set-sink-port 0 "[Out] HeadPhones"
pactl set-sink-volume 0 +5%
sleep 1
pactl set-sink-volume 0 -5%
pacmd set-sink-port 0 "[Out] Speakers"


