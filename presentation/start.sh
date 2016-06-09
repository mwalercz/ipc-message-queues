#!/bin/bash
./build/one_producer_one_consumer/t1_server &
sleep 1
for i in {1..10}
do
   ./build/one_producer_one_consumer/t1_producer &
   ./build/one_producer_one_consumer/t1_consumer &
done
