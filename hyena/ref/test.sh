#!/bin/bash

plain_text="bysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksiaysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksi"
# plain_text="bysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksiaysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksibysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksiaysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksi"
# plain_text="bysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksiaysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksibysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksiaysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksibysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksiaysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksibysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksiaysetatileciksinaysetatileciksinaysetatileciksinaysetatileciksi"

echo "> plain text block size `echo $plain_text | wc -c` byte"

plain_blocks=(`echo $plain_text | sed -r 's/(.{32})/\1 /g'`)
cipher_text=""
enc_clk="0"
dec_clk="0"

for each in "${plain_blocks[@]}"
do
    # echo "$each"
    echo "> plain block size `echo $each | wc -c` byte"
    ./lwbc $each > output 2>&1 & 

    # cipher_text="${}"
    # parse cypher text
    echo "> memory usage `sudo pmap $! | tail -n 1 | awk '{ print $2 }'`"
    sleep 1
    # sed -n '52p'
    lwbc_out=$(cat output)

    cipher_block=$(cat output | sed -n '1p' | awk '{ print $2 }')

    enc_clk_block=$(cat output | sed -n '4p' | awk '{ print $2 }')
    dec_clk_block=$(cat output | sed -n '6p' | awk '{ print $2 }')

    # echo ">>> $enc_clk_block"
    # echo ">>> $enc_clk"
    # echo "$enc_clk + $enc_clk_block" | bc


    enc_clk=`echo "$enc_clk + $enc_clk_block" | bc`
    dec_clk=`echo "$dec_clk + $dec_clk_block" | bc`

    # enc_clk=`echo "$enc_clk + $enc_clk_block" | bc`
    # $enc_clk=echo "$enc_clk + $enc_clk_block" | bc
    echo "$lwbc_out"

    cipher_text="${cipher_text}${cipher_block}"
done

echo "enc clk: $enc_clk" 
echo "dec_clk: $dec_clk"
echo $cipher_text
# rm output
