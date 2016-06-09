#!/bin/bash
for i in {1..50}
do
   ./build/one_producer_one_consumer/t1_producer & ./build/one_producer_one_consumer/t1_consumer
done