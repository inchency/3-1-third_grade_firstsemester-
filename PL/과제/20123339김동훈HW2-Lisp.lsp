; 3.1 memberp  (memberp 'b '(a b c)) => T
(defun memberp (x y) (cond ( (null x) 'nil) 
   ( (atom x) (if (null (member x y) ) 'nil 't))((listp x)
   (if (equalp x (car y)) 't (if (eq (cdr y) nil) 'nil  (memberp x (cdr y))))))) 




; 3.2 union (union '(l m) '(n o p)) => (l m n o p)
(defun union2 (x y)
    (cond ((null x) y)
          ((member (car x) y) (union2 (cdr x) y))
          (t (cons (car x) (union2 (cdr x) y)))))

; 3.3 set-diff (set-diff '(a b c d) '(a d)) => (b c)
(defun set-diff (a b)
  (remove-if
     #'(lambda (x) (and (member x a) (member x b)))
     (append a b)))

; 3.4 subsetp (subsetp '(d f) '(c d e f)) => t

(defun my-union (a b)
  (let ((h (make-hash-table :test #'equal)))
    (mapcar (lambda (x) (setf (gethash x h) x)) a)
    (mapcan (lambda (x) (when (gethash x h) (list x))) b)))
(defun same-elements (a b)
  (apply #'= (mapcar #'length (list (my-union a b) a b))))
(defun subset (a b)
  (same-elements (my-union a b) a))


; 3.5 comp (comp '(l e m o n) '(e o)) => (l m n)
(defun comp (list1 list2)
   (cond ((null list1) nil)
         ((null (car list1)) )
         ((member (car list1) list2) (comp (cdr list1) list2))
         (t (cons (car list1) (comp (cdr list1) list2)))))