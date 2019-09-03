(def arg 6)

(print 'arg=)
(println arg)

(defun fac (n)
    (if (= n 1)
        1
        (* n (fac (- n 1)))))

(print 'fac:)
(println (fac arg))

(defun fib (n)
    (if (> n 1)
        (+ (fib (- n 1)) (fib (- n 2)))
        1))

(print 'fib:)
(println (fib arg))
