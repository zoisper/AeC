//: Playground - noun: a place where people can play

import Cocoa


// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23. Find the sum of all the multiples of 3 or 5 below 1000.


func mults_3_5_a(n : Int) -> Int {
    var i, k : Int
    k = 0;
    i = n-1;
    
    while i>=3 {
        if (i%3==0 || i%5==0) { k+=i }
        i-=1
    }
    
    return k
}

// print(mults_3_5_a(n : 1000))









func mults_3_5_b(n : Int) -> Int {
    var i, k : Int
    k = 0;

    i = 3;
    while i<n {
        k+=i
        i+=3
    }

    i = 5;
    while i<n {
        if !(i%3==0) { k+=i }
        i+=5
    }

    return k
}

print(mults_3_5_b(n : 100000))








// But
//
// 3 + 6 + 9 + ... + max = 3 * (1 + 2 + 3 + ... + max/3)


func sumMultsOf(k : Int, max : Int) -> Int {
    let p : Int = max / k
    return k*p*(p+1)/2
}









func mults_3_5(n : Int) -> Int {
    return sumMultsOf(k:3, max:n-1) + sumMultsOf(k:5, max:n-1) - sumMultsOf(k:15, max:n-1)
}

print(mults_3_5(n : 100000))









