use std::{
    collections::VecDeque,
    fmt,
    io::{self, BufRead},
    str::FromStr,
};

struct Scanner {
    tokens: VecDeque<String>,
}

impl Scanner {
    pub fn new() -> Self {
        let stdin = io::stdin();
        let mut tokens = VecDeque::new();
        for line in stdin.lock().lines() {
            for token in line.unwrap().split_ascii_whitespace() {
                tokens.push_back(token.to_owned());
            }
        }
        Self { tokens }
    }

    pub fn next<T: FromStr>(&mut self) -> T
    where
        <T as FromStr>::Err: fmt::Debug,
    {
        T::from_str(&self.tokens.pop_front().unwrap()).unwrap()
    }
}

fn solve(input: &mut Scanner) {
    let n: i32 = input.next();
    let mut v: Vec<(i32, i32)> = Vec::new();
    for _ in 0..n {
        let a: i32 = input.next();
        let b: i32 = input.next();
        v.push((a, b));
    }

    let mut ans = 0;
    let mut highest_quality = 0;

    for (i, (num_words, quality)) in v.iter().enumerate() {
        if *num_words <= 10 && *quality > highest_quality {
            highest_quality = *quality;
            ans = i + 1;
        }
    }
    println!("{}", ans);
}

fn main() {
    let mut input = Scanner::new();
    let t: i32 = input.next();
    for _ in 0..t {
        solve(&mut input);
    }
}
