//use std::cmp;
//use std::collections::HashMap;
//use std::iter::Iterator;
//use std::string::String;
    
pub struct KMP {
    pattern: Vec<char>,
    lps: Vec<usize>,
    pattern_length: usize
}

impl KMP {
    pub fn new(pattern: &str) -> KMP {
        let pattern: Vec<char> = pattern.chars().collect();
        let pattern_length = pattern.len();
        KMP {
            lps: KMP::find_lps(&pattern),
            pattern: pattern,
            pattern_length: pattern_length
        }
    }

    fn find_lps(pattern: &Vec<char>) -> Vec<usize> {
        let mut i = 1;
        let mut j = 0;
        let pattern_length = pattern.len();
        let end_i = pattern_length - 1;
        let mut lps = vec![0usize; pattern_length];
        while i <= end_i {
            if pattern[i] == pattern[j] {
                lps[i] = j+1;
                i = i+1;
                j = j+1;
            } else {
                if j == 0 {
                    lps[i] = 0;
                    i = i+1;
                } else {
                    j = lps[j-1];
                }
            }
        }
        lps
    }

    pub fn find_index(&self, target: &str) -> Vec<usize> {
        let target: Vec<char> = target.chars().collect();
        let mut t_i: usize = 0;
        let mut p_i: usize = 0;
        let target_len = target.len();
        let mut vec = Vec::new();
        let pattern_len = self.pattern_length;
        while t_i < target_len {
            if target[t_i] == self.pattern[p_i] {
                t_i = t_i+1;
                p_i = p_i+1;
            }
            if p_i == pattern_len {
                vec.push(t_i - p_i);
                p_i = self.lps[p_i-1];
            } else if t_i < target_len && self.pattern[p_i] != target[t_i] {
                if p_i != 0 {
                    p_i = self.lps[p_i-1];
                } else {
                    t_i = t_i+1;
                }
            }
        }
      vec  
    }
    
}


/*pub struct FA {
    pattern: Vec<char>,
    automata: HashMap<(usize, char), usize>,
    pattern_length: usize,
}

impl FA {
    pub fn new(pattern: &str, alphabet: &str) -> FA {
        let a: HashMap<(usize, char), usize>  = FA::find_trans(&pattern, &alphabet);
        let pattern: Vec<char> = pattern.chars().collect();
        let pattern_length = pattern.len();
        let alphabet: Vec<char> = alphabet.chars().collect();
        FA {
            pattern: pattern,
            pattern_length: pattern_length,
            automata: a
        }
    }

    fn find_trans(pattern: &str, alph: &str) -> HashMap<(usize, char), usize> {
        let p = String::from(pattern);
        let a = String::from(alph);
        let mut tf = HashMap::new();
        let p_l = pattern.len();
        for q in 0..(p_l+1) {
            for c in a.chars() {
                let mut k = cmp::min(p_l+1,q+2)-1;
                while !(p[..q].push_str(c)).ends_with(p[..k]) {
                    k = k-1;
                }
                tf.insert((q,c), k);
            }
        }
        tf
    }
    
    pub fn search(&self, text: &str) -> Vec<usize> {
        let mut result = Vec::new();
        let mut q: usize = 0;
        for (i, t) in text.iter().enumerate() {
            q = self.automata[&(q, t)];
            if q == self.pattern_length {
                result.push(i - self.pattern_length +1)
            }
        }
        result
    }
}

*/
