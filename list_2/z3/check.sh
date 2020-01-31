#!/usr/bin/sh

g++ -fpreprocessed -dD -E test.C|sed '/^$/d'|tail -n+2
