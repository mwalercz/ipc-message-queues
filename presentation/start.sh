#!/bin/bash
for i in {1..50}
do
   ./build/one_producer_one_consumer/t1_consumer &
   sleep 4
   ./build/one_producer_one_consumer/t1_producer
done
