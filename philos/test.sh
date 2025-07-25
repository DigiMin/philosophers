#! /usr/bin/env bash

# VARS
PHILO='./philo/bin/philo'
LOG='philo.log'
MEM_LOG='mem_philo.log'

NUM='6'
DIE='250'
EAT='200'
SLEEP='100'
EAT_COUNT='10'
PHILO_ARG="$NUM $DIE $EAT $SLEEP $EAT_COUNT"
# PHILO_ARG="$NUM $DIE $EAT $SLEEP"


EAT_SEARCH=' grep "is eating"'
SLEEP_SEARCH=' grep "is sleeping"'
THINK_SEARCH=' grep "is thinking"'
COUNT_L='wc -l'

# MAKE THE PROJECT EXECUTABLE
make re

# CLEAR LOGS
bash -c "" > $LOG

# TEST
bash -c "$PHILO $PHILO_ARG >> $LOG"

echo -n "Total number of eating activity: "
bash -c "cat $LOG | $EAT_SEARCH | $COUNT_L"

echo -n "Total number of sleeping activity: "
bash -c "cat $LOG | $SLEEP_SEARCH | $COUNT_L"

echo -n "Total number of thinking activity: "
bash -c "cat $LOG | $THINK_SEARCH | $COUNT_L"

echo "" >> $LOG

bash -c "valgrind --tool=helgrind -s --log-file=$MEM_LOG $PHILO $PHILO_ARG >> $LOG"
