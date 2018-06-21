#ifndef CONFIG_H
#define CONFIG_H

#ifdef DATA1
// DATA1 config

#define FILE1 "data/data1/short_1.fasta"
#define FILE2 "data/data1/short_2.fasta"

#define K 30
#define FRAG_LEN 100
#define pair_distance 500
#elif DATA2
// DATA2 config
#define FILE1 "data/data2/short_1.fasta"
#define FILE2 "data/data2/short_2.fasta"

#define K 30
#define FRAG_LEN 1000
#define pair_distance 500

#elif DATA3
// DATA3 config

#elif DATA4
// DATA4 config

#endif
#endif