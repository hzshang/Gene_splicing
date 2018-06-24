#ifndef CONFIG_H
#define CONFIG_H

#ifdef DATA1
// DATA1 config

#define FILE1 "data/data1/short_1.fasta"
#define FILE2 "data/data1/short_2.fasta"

#define K 42
#define FRAG_LEN 100
#define pair_distance 500
#define DIS 6
#define MID_CMP 500
#elif DATA2
// DATA2 config
#define FILE1 "data/data2/short_1.fasta"
#define FILE2 "data/data2/short_2.fasta"

#define K 35
#define FRAG_LEN 100
#define pair_distance 500
#define DIS 6
#define MID_CMP 1500
#elif DATA3
// DATA3 config
#define FILE1 "data/data3/short_1.fasta"
#define FILE2 "data/data3/short_2.fasta"

#define K 28
#define FRAG_LEN 100
#define pair_distance 500
#define DIS 6
#define MID_CMP 1000
#elif DATA4
// DATA4 config
#define FILE1 "data/data4/short_1.fasta"
#define FILE2 "data/data4/short_2.fasta"

#define K 43
#define FRAG_LEN 100
#define pair_distance 500
#define DIS 6
#define MID_CMP 3000
#endif
#endif