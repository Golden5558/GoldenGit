#!/bin/bash

ifconfig -a | grep -i  "ether" | cut -d ' ' -f 10
