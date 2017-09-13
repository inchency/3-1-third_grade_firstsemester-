; �� ���� ������ ���� ��հ� ���
; (average 10 20) => 15
(defun average (x y) (/ (+ x y) 2))

; n factorial ���
; (fact 3) => 6
(defun fact (n)
	(cond ( (<= n 1) 1 )
	      ( t (* n (fact (1- n))))))

; �� ���� ����Ʈ�� �����Ͽ� �ϳ��� ���� - 2��° ����Ʈ�� 1��° ����Ʈ �ڿ� �߰�
; (append2 '(a b) '(c d)) => '(a b c d)

(defun append2 (x y)
	(cond( (null x) y)
	     ( (null (cdr x)) (cons (car x) y) )
	     ( t (cons (car x) (append2 (cdr x) y)) )
	)
)

; ����Ʈ ������ ��������...
; (reverse '(a (b c) e)) => '(e (b c) a)
(defun reverse2 (x)
	(cond ( (atom x) x )
	      ( (null (cdr x)) x )
	      ( t (append (reverse2 (cdr x)) (list (car x))) )
	)
)

; ����Ʈ ������ ��������... ���Ұ� ����Ʈ�̸� �̰͵� ��������...
; (reverse-all '(a (b c d) e)) => '(e (d c b) a)
(defun reverse-all (x)
	(cond ( (atom x) x )
	      ( (null (cdr x)) x )
	      ( t (append (reverse-all (cdr x)) (list (reverse-all (car x)))) )
	)
)
