#!/bin/bash
# Get the number of pages that are used and wired
USED=$(/usr/bin/vm_stat | grep "Pages active" | awk '{print $3}' | sed 's/\.//')
WIRED=$(/usr/bin/vm_stat | grep "Pages wired down" | awk '{print $4}' | sed 's/\.//')

# Get the total number of pages
TOTAL=$(/usr/sbin/sysctl -n hw.memsize | awk '{print $1/4096}' | sed 's/\..*//')

# Calculate the percentage of memory in use
PERCENT_USED=`echo "scale=2; ($(/usr/bin/vm_stat | grep "Pages active" | awk '{print $3}' | sed 's/\.//') + $(/usr/bin/vm_stat | grep "Pages wired down" | awk '{print $4}' | sed 's/\.//')) / $(/usr/sbin/sysctl -n hw.memsize | awk '{print $1/4096}' | sed 's/\..*//') * 100" | bc`

echo "Memory usage: ${PERCENT_USED}%"


# Получаем информацию о размере жесткого диска, доступном месте и использованном месте
DISK_SIZE=$(diskutil info / | grep "Total Size" | awk '{print $4, $5}')
FREE_SPACE=$(df -h / | tail -1 | awk '{print $4}')
USED_SPACE=$(df -h / | tail -1 | awk '{print $3}')

echo "Размер диска: $DISK_SIZE"
echo "Использовано места: $USED_SPACE"
echo "Доступно места: $FREE_SPACE"

IO_STATS=$(iostat -d disk0 | awk 'NR==3{print $2 "," $3}')
READS=$(echo $(iostat -d disk0 | awk 'NR==3{print $2 "," $3}') | cut -d',' -f1)
WRITES=$(echo $IO_STATS | cut -d',' -f2)

echo "$READS"
echo "$WRITES"
echo "scale=2; (${READS}+${WRITES})" | bc