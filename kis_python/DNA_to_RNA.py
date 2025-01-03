'''
Deoxyribonucleic acid, DNA is the primary information storage molecule in biological systems. 
It is composed of four nucleic acid bases Guanine ('G'), Cytosine ('C'), Adenine ('A'), and Thymine ('T').

Ribonucleic acid, RNA, is the primary messenger molecule in cells. 
RNA differs slightly from DNA its chemical structure and contains no Thymine.
 In RNA Thymine is replaced by another nucleic acid Uracil ('U').

Create a function which translates a given DNA string into RNA.

For example:

"GCAT"  =>  "GCAU"
The input string can be of arbitrary length - in particular, it may be empty. 
All input is guaranteed to be valid, i.e. each input string will only ever consist of 'G', 'C', 'A' and/or 'T'.
'''
def dna_to_rna(dna):
    return dna.replace('T','U')


#### Other Solutions
dna_dict = {
    'T': 'U',
    'A': 'A',
    'C': 'C',
    'G': 'G'
}

def DNAtoRNA(dna):
    rna = []
    for letter in dna:
        rna.append(dna_dict[letter])
    return "".join(rna)
#def DNAtoRNA(dna):
#    return "".join([dna_dict[letter] for letter in dna])
# copilot秒杀

#### Other Solutions
DNAtoRNA = lambda d: d.replace("T", "U")

#### Other Solutions
def DNAtoRNA(dna):
    RNA= ""
    i = 0
    for i in dna:
        if i == "T":
            RNA = RNA + "U"
        else:
            RNA = RNA + i
    return RNA

