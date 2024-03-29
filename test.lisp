(def arg 20)

(println "Arg: " arg)

(defun fac (n)
    (if (= n 1)
        1
        (* n (fac (- n 1)))))

(println "Factorial of " arg ": " (fac arg))

(defun fib (n)
    (if (> n 1)
        (+ (fib (- n 1)) (fib (- n 2)))
        1))

(println "Fibonacci at position " arg ": " (fib arg))

(defun exp (a n)
    (if (> n 1)
        (* a (exp a (- n 1)))
        a
    )
)

(defun squared (a) (exp a 2))

(println arg " squared: " (squared arg))

(println)

(times 3 (apply (println "Hey there!") (println "General Kenobi...")))

(println)

(def hello "Hello ")
(def world "World")

(println (concat hello world))
(println "Length: " (len (concat hello world)))