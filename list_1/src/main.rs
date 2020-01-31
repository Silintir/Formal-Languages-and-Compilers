extern crate kmp;
use kmp::KMP;
//use kmp::FA;


fn main() {
    let pattern = r#"0"#;
    let kmp = KMP::new(pattern);
    println!("{:?}",kmp.find_index(r#"78787999997878787879"#));
    let pattern = r#"9"#;
    let kmp = KMP::new(pattern);
    println!("{:?}",kmp.find_index(r#"78787999997878787879"#));
    let pattern = r#"787"#;
    let kmp = KMP::new(pattern);
    println!("{:?}",kmp.find_index(r#"78787999997878787879"#));
    let pattern = r#"99"#;
    let kmp = KMP::new(pattern);
    println!("{:?}",kmp.find_index(r#"78787999997878787879"#));
    let pattern = r#"879"#;
    let kmp = KMP::new(pattern);
    println!("{:?}",kmp.find_index(r#"78787999997878787879"#));
    let pattern = r#"978"#;
    let kmp = KMP::new(pattern);
    println!("{:?}",kmp.find_index(r#"78787999997878787879"#));
    // let fa = FA::new(pattern, alphabet);
}
