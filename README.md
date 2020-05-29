# LZ77
LZ77 algorithms achieve compression by replacing repeated occurrences of data with references to a single copy of that data existing earlier in the uncompressed data stream. A match is encoded by a pair of numbers called a length-distance pair, which is equivalent to the statement "each of the next length characters is equal to the characters exactly distance characters behind it in the uncompressed stream".

| Search Buffer | Forward Buffer | Output |
| ------------- | -------------- | ------ |
|               | abracadabrarra | <0,0,a> |
|            a  | bracadabrarray | <0,0,b> |
|           ab  | racadabrarray  | <0,0,r> |
|          abr  | acadabrarray   | <3,1,c> |
|        abrac  | adabrarray     | <2,1,d> |
|      abracad  | abrarray       | <7,4,r> |

### It is written in c ++ language.
