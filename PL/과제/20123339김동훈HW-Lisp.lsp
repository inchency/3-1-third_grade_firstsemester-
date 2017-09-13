; 1.1 last-item  (last-item '(a b c d)) => d
(defun last-item (x)
	(cond ((null(cdr x))(car x))
		(t (last-item (cdr x)))))



; 1.2 remove-1st   (remove-1st 'a '(b a n a n a)) => (b n a n a)
(defun remove-1st (atm lst)
   (cond ( (not (equal atm (car lst))) (cons (car lst) (remove-1st atm (cdr lst))))
         ( t (cdr lst))))

; 1.2-2 remove-last	(remove-last '(1 2) '(1 2 (1 2) 3))=> (1 2 3)
(defun remove-last (atm lst)
   (reverse (remove-1st atm (reverse lst))))


; 1.3 append   (append '(a b) '(c d e)) => (a b c d e)
(defun append (x y)
	(cond((null (cdr x)) (cons (car x) y))
		(t (cons (car x) (append (cdr x) y)))))


; 1.4 merge     (merge '(1 3 4 7) '(2 4 5)) => (1 2 3 4 4 5 7)
(defun merge (x y)
	(cond   ((null(car x)) y) 
	((null(car y)) x) 
	((< (car x)(car y)) (cons(car x)(merge(cdr x) y)))
	((>=(car x)(car y)) (cons(car y)(merge x (cdr y))))))


; 1.5 subst-all	   (subst-all 'dog 'cat '(my cat is cute)) => (my dog is cute)
	(defun subst-all (atm1 atm2 lst)
	(cond ((null (cdr lst))(cond((equal atm2 (car lst) atm1))(t(car lst))))
	      ((equal atm2 (car lst))(cons atm1(subst-all atm1 atm2(cdr lst))))
	      (t(cons (car lst)(subst-all atm1 atm2 (cdr lst))))))

; 2.1 count -all		(count-all '((a b) c () ((d (e))))) => 6
(defun count-all (x)
   (cond ((null x) 0 )
         ((atom (car x)) (1+ (count-all (cdr x))) )
         	(t(+ (count-all (car x)) (count-all (cdr x))) )))

; 2.2 remove-all2 	(remove-all2 'a '(b (a n) a n a))   => (b (n) n)
(defun remove-all2 (atm lst)
	(cond ((null (car lst)) nil)
	      ((not (atom(car lst))) (cons (remove-all2 atm (car lst)) (remove-all2 atm (cdr lst))))
	      		(t(cond ((equal (car lst) atm) (remove-all2 atm (cdr lst)))
		       		(t(cons (car lst) (remove-all2 atm (cdr lst))))))))



; 2.3 reverse-all	(reverse-all '((1 2) (3 4) 5)) => (5 (4 3) (2 1))
(defun reverse-all (lst)
	(cond ((null (cdr lst))(cond((atom (car lst))(car lst))
		(t (reverse-all(car lst)))))
	     		 ((atom(car lst)) (cons (reverse-all (cdr lst))(car lst)))
	      			(t(cons(reverse-all(cdr lst))(reverse-all(car lst))))))

(defun reverse-all (x)
	(cond ((atom x) x )
	      ((null (cdr x)) x )
	      (t(append(reverse-all(cdr x))(list(reverse-all(car x)))))))



; 2.4 depth		(depth '())   => 0
(defun depth (x)
   (cond ( (atom x) 0 )
         ( t (max (1+ (depth (car x))) (depth (cdr x))))))



; 2.5 flatten		 (flatten '((a b) c (d ((f))))) => (a b c d f)
(defun flatten (x)
   (cond ( (null x) x )
	 ( (atom (car x)) (cons (car x) (flatten (cdr x))) )
	 ( t (append (flatten (car x)) (flatten (cdr x))) )))


