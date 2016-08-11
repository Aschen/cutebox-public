#!/bin/bash

TIME=`date -R -r $1`
mv $1 "$1.old"
touch $1
touch -d "$TIME" $1
