use std::collections::VecDeque;
use std::io::{self, Read};

#[derive(Clone, Copy)]
struct Line {
    m: i128,
    b: i128,
}

fn eval(line: Line, x: i128) -> i128 {
    line.m * x + line.b
}

// l2가 불필요한 직선인지 판별
fn is_bad(l1: Line, l2: Line, l3: Line) -> bool {
    (l2.b - l1.b) * (l2.m - l3.m) >= (l3.b - l2.b) * (l1.m - l2.m)
}

struct Scanner {
    input: Vec<u8>,
    idx: usize,
}

impl Scanner {
    fn new() -> Self {
        let mut input = String::new();
        io::stdin().read_to_string(&mut input).unwrap();
        Self {
            input: input.into_bytes(),
            idx: 0,
        }
    }

    fn next<T: std::str::FromStr>(&mut self) -> T {
        while self.idx < self.input.len() && self.input[self.idx].is_ascii_whitespace() {
            self.idx += 1;
        }
        let start = self.idx;
        while self.idx < self.input.len() && !self.input[self.idx].is_ascii_whitespace() {
            self.idx += 1;
        }
        std::str::from_utf8(&self.input[start..self.idx])
            .unwrap()
            .parse()
            .ok()
            .unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let n: usize = sc.next();

    let mut lands: Vec<(i64, i64)> = Vec::with_capacity(n);
    for _ in 0..n {
        let w: i64 = sc.next();
        let h: i64 = sc.next();
        lands.push((w, h));
    }

    // W 오름차순 정렬
    lands.sort_unstable_by(|a, b| {
        if a.0 == b.0 {
            a.1.cmp(&b.1)
        } else {
            a.0.cmp(&b.0)
        }
    });

    // 같은 W는 H가 가장 큰 것만 남김
    let mut unique: Vec<(i64, i64)> = Vec::new();
    for (w, h) in lands {
        if let Some(last) = unique.last_mut() {
            if last.0 == w {
                if h > last.1 {
                    last.1 = h;
                }
            } else {
                unique.push((w, h));
            }
        } else {
            unique.push((w, h));
        }
    }

    // 뒤에서부터 보며 지배되는 땅 제거
    let mut filtered_rev: Vec<(i64, i64)> = Vec::new();
    let mut max_h = 0i64;
    for &(w, h) in unique.iter().rev() {
        if h > max_h {
            filtered_rev.push((w, h));
            max_h = h;
        }
    }
    filtered_rev.reverse();
    let rects = filtered_rev;

    let m = rects.len();
    let mut dp = vec![0i128; m];
    let mut hull: VecDeque<Line> = VecDeque::new();

    // j = 0 에 해당하는 직선 먼저 추가
    hull.push_back(Line {
        m: rects[0].1 as i128,
        b: 0,
    });

    for i in 0..m {
        let x = rects[i].0 as i128;

        // x가 증가하므로 앞에서부터 최적 직선 유지
        while hull.len() >= 2 {
            let first = hull[0];
            let second = hull[1];
            if eval(second, x) <= eval(first, x) {
                hull.pop_front();
            } else {
                break;
            }
        }

        dp[i] = eval(hull[0], x);

        // 다음 j = i+1 직선 추가
        if i + 1 < m {
            let new_line = Line {
                m: rects[i + 1].1 as i128,
                b: dp[i],
            };

            while hull.len() >= 2 {
                let l1 = hull[hull.len() - 2];
                let l2 = hull[hull.len() - 1];
                if is_bad(l1, l2, new_line) {
                    hull.pop_back();
                } else {
                    break;
                }
            }
            hull.push_back(new_line);
        }
    }

    println!("{}", dp[m - 1]);
}