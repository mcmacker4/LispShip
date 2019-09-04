(def arg 6)

(println "Arg: " arg)

(defun fac (n)
    (if (= n 1)
        1
        (* n (fac (- n 1)))))

(println "Factorial: " (fac arg))

(defun fib (n)
    (if (> n 1)
        (+ (fib (- n 1)) (fib (- n 2)))
        1))

(println "Fibonacci: " (fib arg))
