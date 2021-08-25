#!/bin/bash

filepath="$1"
filename="$2"

title="$3"
author="$4"
year="$5"
publisher="$6"

mv "$filepath/$filename" "../books/[$author] $title [$year] [$publisher]"
