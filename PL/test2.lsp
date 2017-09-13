; ��ø ����Ʈ�� ��ø�� ���� element�鸸 ������ 1���� ���·�...
; (flatten '(a (b) (c (d e)) ((f)))) => '(a b c d e f)
(defun flatten (x)
   (cond ( (null x) x )
;ù��° ���� atom �� ��
	 ( (atom (car x)) (cons (car x) (flatten (cdr x))) )
;ù��° ���� list �� ��
	 ( t (append (flatten (car x)) (flatten (cdr x))) )
   )
)

; atom�� list�� member���� ��(t)/����(nil)���� return
; (memberp 'a '(b a n)) => t
(defun memberp (atm lst)
   (cond  ( (null lst) nil )
          ( (eq atm (car lst)) t )
   	  ( t (memberp atm (cdr lst)) )
   )
)

; ����Ʈ�� ���� ���� count -- ��ø�� �͵� ���� count��!
; (count-all '(a (b c) d)) => 4
(defun count-all (x)
   (cond ( (null x) 0 )
         ( (atom (car x)) (1+ (count-all (cdr x))) )
         ( t (+ (count-all (car x)) (count-all (cdr x))) )))

; lst���� ù��° �߰ߵǴ� atm�� ������
; (remove-1st 'a '(b a n a n a)) => '(b n a n a)
(defun remove-1st (atm lst)
   (cond ( (not (equal atm (car lst))) (cons (car lst) (remove-1st atm (cdr lst))) )
         ( t (cdr lst) )
   )
)

; lst���� ������ �߰ߵǴ� atm�� ������
; (remove-last 'a '(b a n a n a)) => '(b a n a n)
(defun remove-last (atm lst)
   (reverse (remove-1st atm (reverse lst))))

; list�� ���ҵ��� ��������....
; (list-reverse '(a b c d)) => '(c d b a)
(defun list-reverse (list)
   (do ( (x list (cdr x))
         (y '() (cons (car x) y)) )
       ( (endp x) y )
   )
)

; ����Ʈ z�� ���� �߿��� ��� y�� x�� ��ġ��
; (subst2 'c 'a '(b a n a n a)) => '(b c n c n c)
(defun subst2 (x y z)
   (cond ( (equal y z) x )
         ( (atom z) z )
         ( t (cons (subst2 x y (car z)) (subst2 x y (cdr z))) )
   )
)

; ��ø�� ����Ʈ�� ����(depth) ���
; (depth '((a))) => 2, (depth '(a (b (c) d) e)) => 3
(defun depth (x)
   (cond ( (atom x) 0 )
         ( t (max (1+ (depth (car x))) (depth (cdr x))) )
   )
)

;========================================================================
; ������(procedual) ���α׷� ��� ���� -- <����> �Լ��� ��� Ư�� �ƴ�!!!
; �Լ��� ���α׷��� �̷� ������� �ۼ��ϸ� �ȵ�!!!
;========================================================================
(defun sum-of ()
   (prog (n)
	 (princ "Input integer: ")
	 (setq n (read))
  	 (do ( (i 1 (+ i 1))
  	       (sum 0 (+ sum i)) )
   	     ( (> i n) sum )
   	     (princ "1 + ... + ")
   	     (prin1 (1- i))
   	     (princ " = ")
   	     (prin1 sum)
   	     (terpri)
   	 )
   	 (return n)
   )
)

; �� ������ ���α׷��� �Ʒ��� ���� recursion�� �̿��Ͽ� �ۼ��ؾ� ��!!!
(defun sumof (n)
   (cond ( (<= n 1) 1 )
         ( t (+ n (sumof (1- n))) )))

)