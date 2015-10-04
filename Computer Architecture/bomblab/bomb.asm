
bomb:     file format elf32-i386


Disassembly of section .init:

08048760 <_init>:
 8048760:	55                   	push   %ebp
 8048761:	89 e5                	mov    %esp,%ebp
 8048763:	83 ec 08             	sub    $0x8,%esp
 8048766:	e8 e9 01 00 00       	call   8048954 <_start+0x24>
 804876b:	e8 70 02 00 00       	call   80489e0 <_start+0xb0>
 8048770:	e8 cb 16 00 00       	call   8049e40 <__i686.get_pc_thunk.bx+0xb>
 8048775:	c9                   	leave
 8048776:	c3                   	ret

Disassembly of section .plt:

08048780 <read@plt-0x10>:
 8048780:	ff 35 f8 bf 04 08    	pushl  0x804bff8
 8048786:	ff 25 fc bf 04 08    	jmp    *0x804bffc
 804878c:	00 00                	add    %al,(%eax)
	...

08048790 <read@plt>:
 8048790:	ff 25 00 c0 04 08    	jmp    *0x804c000
 8048796:	68 00 00 00 00       	push   $0x0
 804879b:	e9 e0 ff ff ff       	jmp    8048780 <_init+0x20>

080487a0 <fgets@plt>:
 80487a0:	ff 25 04 c0 04 08    	jmp    *0x804c004
 80487a6:	68 08 00 00 00       	push   $0x8
 80487ab:	e9 d0 ff ff ff       	jmp    8048780 <_init+0x20>

080487b0 <signal@plt>:
 80487b0:	ff 25 08 c0 04 08    	jmp    *0x804c008
 80487b6:	68 10 00 00 00       	push   $0x10
 80487bb:	e9 c0 ff ff ff       	jmp    8048780 <_init+0x20>

080487c0 <alarm@plt>:
 80487c0:	ff 25 0c c0 04 08    	jmp    *0x804c00c
 80487c6:	68 18 00 00 00       	push   $0x18
 80487cb:	e9 b0 ff ff ff       	jmp    8048780 <_init+0x20>

080487d0 <strcpy@plt>:
 80487d0:	ff 25 10 c0 04 08    	jmp    *0x804c010
 80487d6:	68 20 00 00 00       	push   $0x20
 80487db:	e9 a0 ff ff ff       	jmp    8048780 <_init+0x20>

080487e0 <gethostname@plt>:
 80487e0:	ff 25 14 c0 04 08    	jmp    *0x804c014
 80487e6:	68 28 00 00 00       	push   $0x28
 80487eb:	e9 90 ff ff ff       	jmp    8048780 <_init+0x20>

080487f0 <getenv@plt>:
 80487f0:	ff 25 18 c0 04 08    	jmp    *0x804c018
 80487f6:	68 30 00 00 00       	push   $0x30
 80487fb:	e9 80 ff ff ff       	jmp    8048780 <_init+0x20>

08048800 <puts@plt>:
 8048800:	ff 25 1c c0 04 08    	jmp    *0x804c01c
 8048806:	68 38 00 00 00       	push   $0x38
 804880b:	e9 70 ff ff ff       	jmp    8048780 <_init+0x20>

08048810 <__memmove_chk@plt>:
 8048810:	ff 25 20 c0 04 08    	jmp    *0x804c020
 8048816:	68 40 00 00 00       	push   $0x40
 804881b:	e9 60 ff ff ff       	jmp    8048780 <_init+0x20>

08048820 <__memcpy_chk@plt>:
 8048820:	ff 25 24 c0 04 08    	jmp    *0x804c024
 8048826:	68 48 00 00 00       	push   $0x48
 804882b:	e9 50 ff ff ff       	jmp    8048780 <_init+0x20>

08048830 <__gmon_start__@plt>:
 8048830:	ff 25 28 c0 04 08    	jmp    *0x804c028
 8048836:	68 50 00 00 00       	push   $0x50
 804883b:	e9 40 ff ff ff       	jmp    8048780 <_init+0x20>

08048840 <exit@plt>:
 8048840:	ff 25 2c c0 04 08    	jmp    *0x804c02c
 8048846:	68 58 00 00 00       	push   $0x58
 804884b:	e9 30 ff ff ff       	jmp    8048780 <_init+0x20>

08048850 <__libc_start_main@plt>:
 8048850:	ff 25 30 c0 04 08    	jmp    *0x804c030
 8048856:	68 60 00 00 00       	push   $0x60
 804885b:	e9 20 ff ff ff       	jmp    8048780 <_init+0x20>

08048860 <write@plt>:
 8048860:	ff 25 34 c0 04 08    	jmp    *0x804c034
 8048866:	68 68 00 00 00       	push   $0x68
 804886b:	e9 10 ff ff ff       	jmp    8048780 <_init+0x20>

08048870 <__isoc99_sscanf@plt>:
 8048870:	ff 25 38 c0 04 08    	jmp    *0x804c038
 8048876:	68 70 00 00 00       	push   $0x70
 804887b:	e9 00 ff ff ff       	jmp    8048780 <_init+0x20>

08048880 <fopen@plt>:
 8048880:	ff 25 3c c0 04 08    	jmp    *0x804c03c
 8048886:	68 78 00 00 00       	push   $0x78
 804888b:	e9 f0 fe ff ff       	jmp    8048780 <_init+0x20>

08048890 <__errno_location@plt>:
 8048890:	ff 25 40 c0 04 08    	jmp    *0x804c040
 8048896:	68 80 00 00 00       	push   $0x80
 804889b:	e9 e0 fe ff ff       	jmp    8048780 <_init+0x20>

080488a0 <__printf_chk@plt>:
 80488a0:	ff 25 44 c0 04 08    	jmp    *0x804c044
 80488a6:	68 88 00 00 00       	push   $0x88
 80488ab:	e9 d0 fe ff ff       	jmp    8048780 <_init+0x20>

080488b0 <socket@plt>:
 80488b0:	ff 25 48 c0 04 08    	jmp    *0x804c048
 80488b6:	68 90 00 00 00       	push   $0x90
 80488bb:	e9 c0 fe ff ff       	jmp    8048780 <_init+0x20>

080488c0 <__fprintf_chk@plt>:
 80488c0:	ff 25 4c c0 04 08    	jmp    *0x804c04c
 80488c6:	68 98 00 00 00       	push   $0x98
 80488cb:	e9 b0 fe ff ff       	jmp    8048780 <_init+0x20>

080488d0 <gethostbyname@plt>:
 80488d0:	ff 25 50 c0 04 08    	jmp    *0x804c050
 80488d6:	68 a0 00 00 00       	push   $0xa0
 80488db:	e9 a0 fe ff ff       	jmp    8048780 <_init+0x20>

080488e0 <strtol@plt>:
 80488e0:	ff 25 54 c0 04 08    	jmp    *0x804c054
 80488e6:	68 a8 00 00 00       	push   $0xa8
 80488eb:	e9 90 fe ff ff       	jmp    8048780 <_init+0x20>

080488f0 <connect@plt>:
 80488f0:	ff 25 58 c0 04 08    	jmp    *0x804c058
 80488f6:	68 b0 00 00 00       	push   $0xb0
 80488fb:	e9 80 fe ff ff       	jmp    8048780 <_init+0x20>

08048900 <close@plt>:
 8048900:	ff 25 5c c0 04 08    	jmp    *0x804c05c
 8048906:	68 b8 00 00 00       	push   $0xb8
 804890b:	e9 70 fe ff ff       	jmp    8048780 <_init+0x20>

08048910 <__ctype_b_loc@plt>:
 8048910:	ff 25 60 c0 04 08    	jmp    *0x804c060
 8048916:	68 c0 00 00 00       	push   $0xc0
 804891b:	e9 60 fe ff ff       	jmp    8048780 <_init+0x20>

08048920 <__sprintf_chk@plt>:
 8048920:	ff 25 64 c0 04 08    	jmp    *0x804c064
 8048926:	68 c8 00 00 00       	push   $0xc8
 804892b:	e9 50 fe ff ff       	jmp    8048780 <_init+0x20>

Disassembly of section .text:

08048930 <_start>:
 8048930:	31 ed                	xor    %ebp,%ebp
 8048932:	5e                   	pop    %esi
 8048933:	89 e1                	mov    %esp,%ecx
 8048935:	83 e4 f0             	and    $0xfffffff0,%esp
 8048938:	50                   	push   %eax
 8048939:	54                   	push   %esp
 804893a:	52                   	push   %edx
 804893b:	68 30 9e 04 08       	push   $0x8049e30
 8048940:	68 d0 9d 04 08       	push   $0x8049dd0
 8048945:	51                   	push   %ecx
 8048946:	56                   	push   %esi
 8048947:	68 04 8a 04 08       	push   $0x8048a04
 804894c:	e8 ff fe ff ff       	call   8048850 <__libc_start_main@plt>
 8048951:	f4                   	hlt
 8048952:	90                   	nop
 8048953:	90                   	nop
 8048954:	55                   	push   %ebp
 8048955:	89 e5                	mov    %esp,%ebp
 8048957:	53                   	push   %ebx
 8048958:	83 ec 04             	sub    $0x4,%esp
 804895b:	e8 00 00 00 00       	call   8048960 <_start+0x30>
 8048960:	5b                   	pop    %ebx
 8048961:	81 c3 94 36 00 00    	add    $0x3694,%ebx
 8048967:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 804896d:	85 d2                	test   %edx,%edx
 804896f:	74 05                	je     8048976 <_start+0x46>
 8048971:	e8 ba fe ff ff       	call   8048830 <__gmon_start__@plt>
 8048976:	58                   	pop    %eax
 8048977:	5b                   	pop    %ebx
 8048978:	c9                   	leave
 8048979:	c3                   	ret
 804897a:	90                   	nop
 804897b:	90                   	nop
 804897c:	90                   	nop
 804897d:	90                   	nop
 804897e:	90                   	nop
 804897f:	90                   	nop
 8048980:	55                   	push   %ebp
 8048981:	89 e5                	mov    %esp,%ebp
 8048983:	53                   	push   %ebx
 8048984:	83 ec 04             	sub    $0x4,%esp
 8048987:	80 3d c8 c5 04 08 00 	cmpb   $0x0,0x804c5c8
 804898e:	75 3f                	jne    80489cf <_start+0x9f>
 8048990:	a1 cc c5 04 08       	mov    0x804c5cc,%eax
 8048995:	bb 18 bf 04 08       	mov    $0x804bf18,%ebx
 804899a:	81 eb 14 bf 04 08    	sub    $0x804bf14,%ebx
 80489a0:	c1 fb 02             	sar    $0x2,%ebx
 80489a3:	83 eb 01             	sub    $0x1,%ebx
 80489a6:	39 d8                	cmp    %ebx,%eax
 80489a8:	73 1e                	jae    80489c8 <_start+0x98>
 80489aa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 80489b0:	83 c0 01             	add    $0x1,%eax
 80489b3:	a3 cc c5 04 08       	mov    %eax,0x804c5cc
 80489b8:	ff 14 85 14 bf 04 08 	call   *0x804bf14(,%eax,4)
 80489bf:	a1 cc c5 04 08       	mov    0x804c5cc,%eax
 80489c4:	39 d8                	cmp    %ebx,%eax
 80489c6:	72 e8                	jb     80489b0 <_start+0x80>
 80489c8:	c6 05 c8 c5 04 08 01 	movb   $0x1,0x804c5c8
 80489cf:	83 c4 04             	add    $0x4,%esp
 80489d2:	5b                   	pop    %ebx
 80489d3:	5d                   	pop    %ebp
 80489d4:	c3                   	ret
 80489d5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 80489d9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
 80489e0:	55                   	push   %ebp
 80489e1:	89 e5                	mov    %esp,%ebp
 80489e3:	83 ec 18             	sub    $0x18,%esp
 80489e6:	a1 1c bf 04 08       	mov    0x804bf1c,%eax
 80489eb:	85 c0                	test   %eax,%eax
 80489ed:	74 12                	je     8048a01 <_start+0xd1>
 80489ef:	b8 00 00 00 00       	mov    $0x0,%eax
 80489f4:	85 c0                	test   %eax,%eax
 80489f6:	74 09                	je     8048a01 <_start+0xd1>
 80489f8:	c7 04 24 1c bf 04 08 	movl   $0x804bf1c,(%esp)
 80489ff:	ff d0                	call   *%eax
 8048a01:	c9                   	leave
 8048a02:	c3                   	ret
 8048a03:	90                   	nop

08048a04 <main>:
 8048a04:	55                   	push   %ebp
 8048a05:	89 e5                	mov    %esp,%ebp
 8048a07:	53                   	push   %ebx
 8048a08:	83 e4 f0             	and    $0xfffffff0,%esp
 8048a0b:	83 ec 10             	sub    $0x10,%esp
 8048a0e:	8b 45 08             	mov    0x8(%ebp),%eax
 8048a11:	8b 5d 0c             	mov    0xc(%ebp),%ebx
 8048a14:	83 f8 01             	cmp    $0x1,%eax
 8048a17:	75 0c                	jne    8048a25 <main+0x21>
 8048a19:	a1 c4 c5 04 08       	mov    0x804c5c4,%eax
 8048a1e:	a3 00 c8 04 08       	mov    %eax,0x804c800
 8048a23:	eb 74                	jmp    8048a99 <main+0x95>
 8048a25:	83 f8 02             	cmp    $0x2,%eax
 8048a28:	75 49                	jne    8048a73 <main+0x6f>
 8048a2a:	c7 44 24 04 ed a2 04 	movl   $0x804a2ed,0x4(%esp)
 8048a31:	08
 8048a32:	8b 43 04             	mov    0x4(%ebx),%eax
 8048a35:	89 04 24             	mov    %eax,(%esp)
 8048a38:	e8 43 fe ff ff       	call   8048880 <fopen@plt>
 8048a3d:	a3 00 c8 04 08       	mov    %eax,0x804c800
 8048a42:	85 c0                	test   %eax,%eax
 8048a44:	75 53                	jne    8048a99 <main+0x95>
 8048a46:	8b 43 04             	mov    0x4(%ebx),%eax
 8048a49:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048a4d:	8b 03                	mov    (%ebx),%eax
 8048a4f:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048a53:	c7 44 24 04 a8 9e 04 	movl   $0x8049ea8,0x4(%esp)
 8048a5a:	08
 8048a5b:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048a62:	e8 39 fe ff ff       	call   80488a0 <__printf_chk@plt>
 8048a67:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048a6e:	e8 cd fd ff ff       	call   8048840 <exit@plt>
 8048a73:	8b 03                	mov    (%ebx),%eax
 8048a75:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048a79:	c7 44 24 04 c5 9e 04 	movl   $0x8049ec5,0x4(%esp)
 8048a80:	08
 8048a81:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048a88:	e8 13 fe ff ff       	call   80488a0 <__printf_chk@plt>
 8048a8d:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048a94:	e8 a7 fd ff ff       	call   8048840 <exit@plt>
 8048a99:	e8 7f 05 00 00       	call   804901d <initialize_bomb>
 8048a9e:	c7 04 24 2c 9f 04 08 	movl   $0x8049f2c,(%esp)
 8048aa5:	e8 56 fd ff ff       	call   8048800 <puts@plt>
 8048aaa:	c7 04 24 68 9f 04 08 	movl   $0x8049f68,(%esp)
 8048ab1:	e8 4a fd ff ff       	call   8048800 <puts@plt>
 8048ab6:	e8 87 07 00 00       	call   8049242 <read_line>
 8048abb:	89 04 24             	mov    %eax,(%esp)
 8048abe:	e8 a5 00 00 00       	call   8048b68 <phase_1>
 8048ac3:	e8 bf 08 00 00       	call   8049387 <phase_defused>
 8048ac8:	c7 04 24 94 9f 04 08 	movl   $0x8049f94,(%esp)
 8048acf:	e8 2c fd ff ff       	call   8048800 <puts@plt>
 8048ad4:	e8 69 07 00 00       	call   8049242 <read_line>
 8048ad9:	89 04 24             	mov    %eax,(%esp)
 8048adc:	e8 b0 00 00 00       	call   8048b91 <phase_2>
 8048ae1:	e8 a1 08 00 00       	call   8049387 <phase_defused>
 8048ae6:	c7 04 24 df 9e 04 08 	movl   $0x8049edf,(%esp)
 8048aed:	e8 0e fd ff ff       	call   8048800 <puts@plt>
 8048af2:	e8 4b 07 00 00       	call   8049242 <read_line>
 8048af7:	89 04 24             	mov    %eax,(%esp)
 8048afa:	e8 df 00 00 00       	call   8048bde <phase_3>
 8048aff:	e8 83 08 00 00       	call   8049387 <phase_defused>
 8048b04:	c7 04 24 fd 9e 04 08 	movl   $0x8049efd,(%esp)
 8048b0b:	e8 f0 fc ff ff       	call   8048800 <puts@plt>
 8048b10:	e8 2d 07 00 00       	call   8049242 <read_line>
 8048b15:	89 04 24             	mov    %eax,(%esp)
 8048b18:	e8 ef 01 00 00       	call   8048d0c <phase_4>
 8048b1d:	e8 65 08 00 00       	call   8049387 <phase_defused>
 8048b22:	c7 04 24 c0 9f 04 08 	movl   $0x8049fc0,(%esp)
 8048b29:	e8 d2 fc ff ff       	call   8048800 <puts@plt>
 8048b2e:	e8 0f 07 00 00       	call   8049242 <read_line>
 8048b33:	89 04 24             	mov    %eax,(%esp)
 8048b36:	e8 45 02 00 00       	call   8048d80 <phase_5>
 8048b3b:	e8 47 08 00 00       	call   8049387 <phase_defused>
 8048b40:	c7 04 24 0c 9f 04 08 	movl   $0x8049f0c,(%esp)
 8048b47:	e8 b4 fc ff ff       	call   8048800 <puts@plt>
 8048b4c:	e8 f1 06 00 00       	call   8049242 <read_line>
 8048b51:	89 04 24             	mov    %eax,(%esp)
 8048b54:	e8 73 02 00 00       	call   8048dcc <phase_6>
 8048b59:	e8 29 08 00 00       	call   8049387 <phase_defused>
 8048b5e:	b8 00 00 00 00       	mov    $0x0,%eax
 8048b63:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 8048b66:	c9                   	leave
 8048b67:	c3                   	ret

08048b68 <phase_1>:
 8048b68:	83 ec 1c             	sub    $0x1c,%esp
 8048b6b:	e8 02 11 00 00       	call   8049c72 <phase_init>
 8048b70:	c7 44 24 04 e4 9f 04 	movl   $0x8049fe4,0x4(%esp)
 8048b77:	08
 8048b78:	8b 44 24 20          	mov    0x20(%esp),%eax
 8048b7c:	89 04 24             	mov    %eax,(%esp)
 8048b7f:	e8 2e 04 00 00       	call   8048fb2 <strings_not_equal>
 8048b84:	85 c0                	test   %eax,%eax
 8048b86:	74 05                	je     8048b8d <phase_1+0x25>
 8048b88:	e8 82 06 00 00       	call   804920f <explode_bomb>
 8048b8d:	83 c4 1c             	add    $0x1c,%esp
 8048b90:	c3                   	ret

08048b91 <phase_2>:
 8048b91:	56                   	push   %esi
 8048b92:	53                   	push   %ebx
 8048b93:	83 ec 34             	sub    $0x34,%esp
 8048b96:	e8 d7 10 00 00       	call   8049c72 <phase_init>
 8048b9b:	8d 44 24 18          	lea    0x18(%esp),%eax
 8048b9f:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048ba3:	8b 44 24 40          	mov    0x40(%esp),%eax
 8048ba7:	89 04 24             	mov    %eax,(%esp)
 8048baa:	e8 88 07 00 00       	call   8049337 <read_six_numbers>
 8048baf:	83 7c 24 18 03       	cmpl   $0x3,0x18(%esp)
 8048bb4:	74 05                	je     8048bbb <phase_2+0x2a>
 8048bb6:	e8 54 06 00 00       	call   804920f <explode_bomb>
 8048bbb:	8d 5c 24 1c          	lea    0x1c(%esp),%ebx
 8048bbf:	8d 74 24 30          	lea    0x30(%esp),%esi
 8048bc3:	8b 43 fc             	mov    -0x4(%ebx),%eax
 8048bc6:	d1 e0                	shl    %eax
 8048bc8:	39 03                	cmp    %eax,(%ebx)
 8048bca:	74 05                	je     8048bd1 <phase_2+0x40>
 8048bcc:	e8 3e 06 00 00       	call   804920f <explode_bomb>
 8048bd1:	83 c3 04             	add    $0x4,%ebx
 8048bd4:	39 f3                	cmp    %esi,%ebx
 8048bd6:	75 eb                	jne    8048bc3 <phase_2+0x32>
 8048bd8:	83 c4 34             	add    $0x34,%esp
 8048bdb:	5b                   	pop    %ebx
 8048bdc:	5e                   	pop    %esi
 8048bdd:	c3                   	ret

08048bde <phase_3>:
 8048bde:	83 ec 2c             	sub    $0x2c,%esp
 8048be1:	e8 8c 10 00 00       	call   8049c72 <phase_init>
 8048be6:	8d 44 24 18          	lea    0x18(%esp),%eax
 8048bea:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048bee:	8d 44 24 1c          	lea    0x1c(%esp),%eax
 8048bf2:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048bf6:	c7 44 24 04 d5 a2 04 	movl   $0x804a2d5,0x4(%esp)
 8048bfd:	08
 8048bfe:	8b 44 24 30          	mov    0x30(%esp),%eax
 8048c02:	89 04 24             	mov    %eax,(%esp)
 8048c05:	e8 66 fc ff ff       	call   8048870 <__isoc99_sscanf@plt>
 8048c0a:	83 f8 01             	cmp    $0x1,%eax
 8048c0d:	7f 05                	jg     8048c14 <phase_3+0x36>
 8048c0f:	e8 fb 05 00 00       	call   804920f <explode_bomb>
 8048c14:	83 7c 24 1c 08       	cmpl   $0x8,0x1c(%esp)
 8048c19:	77 72                	ja     8048c8d <phase_3+0xaf>
 8048c1b:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 8048c1f:	ff 24 85 40 a0 04 08 	jmp    *0x804a040(,%eax,4)
 8048c26:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c2b:	eb 05                	jmp    8048c32 <phase_3+0x54>
 8048c2d:	b8 e3 03 00 00       	mov    $0x3e3,%eax
 8048c32:	2d c0 00 00 00       	sub    $0xc0,%eax
 8048c37:	eb 05                	jmp    8048c3e <phase_3+0x60>
 8048c39:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c3e:	05 71 02 00 00       	add    $0x271,%eax
 8048c43:	eb 05                	jmp    8048c4a <phase_3+0x6c>
 8048c45:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c4a:	2d 37 02 00 00       	sub    $0x237,%eax
 8048c4f:	eb 05                	jmp    8048c56 <phase_3+0x78>
 8048c51:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c56:	05 fb 01 00 00       	add    $0x1fb,%eax
 8048c5b:	eb 05                	jmp    8048c62 <phase_3+0x84>
 8048c5d:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c62:	2d fb 01 00 00       	sub    $0x1fb,%eax
 8048c67:	eb 05                	jmp    8048c6e <phase_3+0x90>
 8048c69:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c6e:	05 fb 01 00 00       	add    $0x1fb,%eax
 8048c73:	eb 05                	jmp    8048c7a <phase_3+0x9c>
 8048c75:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c7a:	2d fb 01 00 00       	sub    $0x1fb,%eax
 8048c7f:	eb 05                	jmp    8048c86 <phase_3+0xa8>
 8048c81:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c86:	05 fb 01 00 00       	add    $0x1fb,%eax
 8048c8b:	eb 0a                	jmp    8048c97 <phase_3+0xb9>
 8048c8d:	e8 7d 05 00 00       	call   804920f <explode_bomb>
 8048c92:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c97:	83 7c 24 1c 05       	cmpl   $0x5,0x1c(%esp)
 8048c9c:	7f 06                	jg     8048ca4 <phase_3+0xc6>
 8048c9e:	3b 44 24 18          	cmp    0x18(%esp),%eax
 8048ca2:	74 05                	je     8048ca9 <phase_3+0xcb>
 8048ca4:	e8 66 05 00 00       	call   804920f <explode_bomb>
 8048ca9:	83 c4 2c             	add    $0x2c,%esp
 8048cac:	c3                   	ret

08048cad <func4>:
 8048cad:	56                   	push   %esi
 8048cae:	53                   	push   %ebx
 8048caf:	83 ec 14             	sub    $0x14,%esp
 8048cb2:	8b 44 24 20          	mov    0x20(%esp),%eax
 8048cb6:	8b 4c 24 24          	mov    0x24(%esp),%ecx
 8048cba:	8b 5c 24 28          	mov    0x28(%esp),%ebx
 8048cbe:	89 da                	mov    %ebx,%edx
 8048cc0:	29 ca                	sub    %ecx,%edx
 8048cc2:	89 d6                	mov    %edx,%esi
 8048cc4:	c1 ee 1f             	shr    $0x1f,%esi
 8048cc7:	01 f2                	add    %esi,%edx
 8048cc9:	d1 fa                	sar    %edx
 8048ccb:	01 ca                	add    %ecx,%edx
 8048ccd:	39 c2                	cmp    %eax,%edx
 8048ccf:	7e 17                	jle    8048ce8 <func4+0x3b>
 8048cd1:	4a                   	dec    %edx
 8048cd2:	89 54 24 08          	mov    %edx,0x8(%esp)
 8048cd6:	89 4c 24 04          	mov    %ecx,0x4(%esp)
 8048cda:	89 04 24             	mov    %eax,(%esp)
 8048cdd:	e8 cb ff ff ff       	call   8048cad <func4>
 8048ce2:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048ce6:	eb 1e                	jmp    8048d06 <func4+0x59>
 8048ce8:	39 c2                	cmp    %eax,%edx
 8048cea:	7d 15                	jge    8048d01 <func4+0x54>
 8048cec:	89 5c 24 08          	mov    %ebx,0x8(%esp)
 8048cf0:	42                   	inc    %edx
 8048cf1:	89 54 24 04          	mov    %edx,0x4(%esp)
 8048cf5:	89 04 24             	mov    %eax,(%esp)
 8048cf8:	e8 b0 ff ff ff       	call   8048cad <func4>
 8048cfd:	d1 e0                	shl    %eax
 8048cff:	eb 05                	jmp    8048d06 <func4+0x59>
 8048d01:	b8 00 00 00 00       	mov    $0x0,%eax
 8048d06:	83 c4 14             	add    $0x14,%esp
 8048d09:	5b                   	pop    %ebx
 8048d0a:	5e                   	pop    %esi
 8048d0b:	c3                   	ret

08048d0c <phase_4>:
 8048d0c:	83 ec 2c             	sub    $0x2c,%esp
 8048d0f:	e8 5e 0f 00 00       	call   8049c72 <phase_init>
 8048d14:	8d 44 24 18          	lea    0x18(%esp),%eax
 8048d18:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048d1c:	8d 44 24 1c          	lea    0x1c(%esp),%eax
 8048d20:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048d24:	c7 44 24 04 d5 a2 04 	movl   $0x804a2d5,0x4(%esp)
 8048d2b:	08
 8048d2c:	8b 44 24 30          	mov    0x30(%esp),%eax
 8048d30:	89 04 24             	mov    %eax,(%esp)
 8048d33:	e8 38 fb ff ff       	call   8048870 <__isoc99_sscanf@plt>
 8048d38:	83 f8 02             	cmp    $0x2,%eax
 8048d3b:	75 0d                	jne    8048d4a <phase_4+0x3e>
 8048d3d:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 8048d41:	85 c0                	test   %eax,%eax
 8048d43:	78 05                	js     8048d4a <phase_4+0x3e>
 8048d45:	83 f8 0e             	cmp    $0xe,%eax
 8048d48:	7e 05                	jle    8048d4f <phase_4+0x43>
 8048d4a:	e8 c0 04 00 00       	call   804920f <explode_bomb>
 8048d4f:	c7 44 24 08 0e 00 00 	movl   $0xe,0x8(%esp)
 8048d56:	00
 8048d57:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 8048d5e:	00
 8048d5f:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 8048d63:	89 04 24             	mov    %eax,(%esp)
 8048d66:	e8 42 ff ff ff       	call   8048cad <func4>
 8048d6b:	83 f8 03             	cmp    $0x3,%eax
 8048d6e:	75 07                	jne    8048d77 <phase_4+0x6b>
 8048d70:	83 7c 24 18 03       	cmpl   $0x3,0x18(%esp)
 8048d75:	74 05                	je     8048d7c <phase_4+0x70>
 8048d77:	e8 93 04 00 00       	call   804920f <explode_bomb>
 8048d7c:	83 c4 2c             	add    $0x2c,%esp
 8048d7f:	c3                   	ret

08048d80 <phase_5>:
 8048d80:	53                   	push   %ebx
 8048d81:	83 ec 18             	sub    $0x18,%esp
 8048d84:	8b 5c 24 20          	mov    0x20(%esp),%ebx
 8048d88:	e8 e5 0e 00 00       	call   8049c72 <phase_init>
 8048d8d:	89 1c 24             	mov    %ebx,(%esp)
 8048d90:	e8 01 02 00 00       	call   8048f96 <string_length>
 8048d95:	83 f8 06             	cmp    $0x6,%eax
 8048d98:	74 05                	je     8048d9f <phase_5+0x1f>
 8048d9a:	e8 70 04 00 00       	call   804920f <explode_bomb>
 8048d9f:	ba 00 00 00 00       	mov    $0x0,%edx
 8048da4:	b8 00 00 00 00       	mov    $0x0,%eax
 8048da9:	0f be 0c 03          	movsbl (%ebx,%eax,1),%ecx
 8048dad:	83 e1 0f             	and    $0xf,%ecx
 8048db0:	03 14 8d 80 a0 04 08 	add    0x804a080(,%ecx,4),%edx
 8048db7:	40                   	inc    %eax
 8048db8:	83 f8 06             	cmp    $0x6,%eax
 8048dbb:	75 ec                	jne    8048da9 <phase_5+0x29>
 8048dbd:	83 fa 17             	cmp    $0x17,%edx
 8048dc0:	74 05                	je     8048dc7 <phase_5+0x47>
 8048dc2:	e8 48 04 00 00       	call   804920f <explode_bomb>
 8048dc7:	83 c4 18             	add    $0x18,%esp
 8048dca:	5b                   	pop    %ebx
 8048dcb:	c3                   	ret

08048dcc <phase_6>:
 8048dcc:	56                   	push   %esi
 8048dcd:	53                   	push   %ebx
 8048dce:	83 ec 44             	sub    $0x44,%esp
 8048dd1:	e8 9c 0e 00 00       	call   8049c72 <phase_init>
 8048dd6:	8d 44 24 28          	lea    0x28(%esp),%eax
 8048dda:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048dde:	8b 44 24 50          	mov    0x50(%esp),%eax
 8048de2:	89 04 24             	mov    %eax,(%esp)
 8048de5:	e8 4d 05 00 00       	call   8049337 <read_six_numbers>

 숫자를 받아서
 8048dea:	be 00 00 00 00       	mov    $0x0,%esi
 8048def:	8b 44 b4 28          	mov    0x28(%esp,%esi,4),%eax   <- phase_6 + 0x23
 8048df3:	48                   	dec    %eax
 8048df4:	83 f8 05             	cmp    $0x5,%eax                첫번째 숫자가 6보다 작거나 같은가?
 8048df7:	76 05                	jbe    8048dfe <phase_6+0x32>
 8048df9:	e8 11 04 00 00       	call   804920f <explode_bomb>
 8048dfe:	46                   	inc    %esi
 8048dff:	83 fe 06             	cmp    $0x6,%esi                루프문 탈출하는 명령어, 6번만 돌고 탈출
 8048e02:	74 37                	je     8048e3b <phase_6+0x6f>
 8048e04:	89 f3                	mov    %esi,%ebx
 8048e06:	8b 44 9c 28          	mov    0x28(%esp,%ebx,4),%eax   <- phase_6 + 0x3a
 8048e0a:	39 44 b4 24          	cmp    %eax,0x24(%esp,%esi,4)
 8048e0e:	75 05                	jne    8048e15 <phase_6+0x49>   같은 숫자가 연속으로 있으면 뻥
 8048e10:	e8 fa 03 00 00       	call   804920f <explode_bomb>
 8048e15:	43                   	inc    %ebx
 8048e16:	83 fb 05             	cmp    $0x5,%ebx                루프문 탈출하는 명령어
 8048e19:	7e eb                	jle    8048e06 <phase_6+0x3a>
 8048e1b:	eb d2                	jmp    8048def <phase_6+0x23>
 8048e1d:	b8 01 00 00 00       	mov    $0x1,%eax
 8048e22:	ba 54 c1 04 08       	mov    $0x804c154,%edx
 8048e27:	8b 52 08             	mov    0x8(%edx),%edx
 8048e2a:	40                   	inc    %eax
 8048e2b:	39 c8                	cmp    %ecx,%eax
 8048e2d:	75 f8                	jne    8048e27 <phase_6+0x5b>
 8048e2f:	89 54 b4 10          	mov    %edx,0x10(%esp,%esi,4)
 8048e33:	43                   	inc    %ebx
 8048e34:	83 fb 06             	cmp    $0x6,%ebx
 8048e37:	75 07                	jne    8048e40 <phase_6+0x74>
 8048e39:	eb 17                	jmp    8048e52 <phase_6+0x86>





 8048e3b:	bb 00 00 00 00       	mov    $0x0,%ebx                <- 루프 끝나면 오는곳
 8048e40:	89 de                	mov    %ebx,%esi
 8048e42:	8b 4c 9c 28          	mov    0x28(%esp,%ebx,4),%ecx
 8048e46:	83 f9 01             	cmp    $0x1,%ecx
 8048e49:	7f d2                	jg     8048e1d <phase_6+0x51>
 8048e4b:	ba 54 c1 04 08       	mov    $0x804c154,%edx
 8048e50:	eb dd                	jmp    8048e2f <phase_6+0x63>
 8048e52:	8b 5c 24 10          	mov    0x10(%esp),%ebx      ebx = &node2
 8048e56:	8b 44 24 14          	mov    0x14(%esp),%eax      eax = &node6
 8048e5a:	89 43 08             	mov    %eax,0x8(%ebx)                      node2 -> node6
 8048e5d:	8b 54 24 18          	mov    0x18(%esp),%edx      edx = &node1
 8048e61:	89 50 08             	mov    %edx,0x8(%eax)                      node6 -> node1
 8048e64:	8b 44 24 1c          	mov    0x1c(%esp),%eax      eax = &node3
 8048e68:	89 42 08             	mov    %eax,0x8(%edx)                      node1 -> node3
 8048e6b:	8b 54 24 20          	mov    0x20(%esp),%edx      edx = &node5
 8048e6f:	89 50 08             	mov    %edx,0x8(%eax)                      node3 -> node5
 8048e72:	8b 44 24 24          	mov    0x24(%esp),%eax      eax = &node4
 8048e76:	89 42 08             	mov    %eax,0x8(%edx)                      node5 -> node4
 8048e79:	c7 40 08 00 00 00 00 	movl   $0x0,0x8(%eax)                      node4 -> NULL



 8048e80:	be 05 00 00 00       	mov    $0x5,%esi                           esi = 5
 8048e85:	8b 43 08             	mov    0x8(%ebx),%eax                      eax = node2.next
 8048e88:	8b 10                	mov    (%eax),%edx                         edx = *eax = *node2.next = node6 (254)
 8048e8a:	39 13                	cmp    %edx,(%ebx)                         node6, *ebx 비교 (node6, node2 == 254, 203)
 8048e8c:	7d 05                	jge    8048e93 <phase_6+0xc7>
 8048e8e:	e8 7c 03 00 00       	call   804920f <explode_bomb>
 8048e93:	8b 5b 08             	mov    0x8(%ebx),%ebx
 8048e96:	4e                   	dec    %esi
 8048e97:	75 ec                	jne    8048e85 <phase_6+0xb9>
 8048e99:	83 c4 44             	add    $0x44,%esp
 8048e9c:	5b                   	pop    %ebx
 8048e9d:	5e                   	pop    %esi
 8048e9e:	c3                   	ret

08048e9f <fun7>:
 8048e9f:	83 ec 1c             	sub    $0x1c,%esp
 8048ea2:	8b 44 24 20          	mov    0x20(%esp),%eax
 8048ea6:	8b 54 24 24          	mov    0x24(%esp),%edx
 8048eaa:	85 c0                	test   %eax,%eax
 8048eac:	74 32                	je     8048ee0 <fun7+0x41>
 8048eae:	8b 08                	mov    (%eax),%ecx
 8048eb0:	39 d1                	cmp    %edx,%ecx
 8048eb2:	7e 13                	jle    8048ec7 <fun7+0x28>
 8048eb4:	89 54 24 04          	mov    %edx,0x4(%esp)
 8048eb8:	8b 40 04             	mov    0x4(%eax),%eax
 8048ebb:	89 04 24             	mov    %eax,(%esp)
 8048ebe:	e8 dc ff ff ff       	call   8048e9f <fun7>
 8048ec3:	d1 e0                	shl    %eax
 8048ec5:	eb 25                	jmp    8048eec <fun7+0x4d>
 8048ec7:	39 d1                	cmp    %edx,%ecx
 8048ec9:	74 1c                	je     8048ee7 <fun7+0x48>
 8048ecb:	89 54 24 04          	mov    %edx,0x4(%esp)
 8048ecf:	8b 40 08             	mov    0x8(%eax),%eax
 8048ed2:	89 04 24             	mov    %eax,(%esp)
 8048ed5:	e8 c5 ff ff ff       	call   8048e9f <fun7>
 8048eda:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048ede:	eb 0c                	jmp    8048eec <fun7+0x4d>
 8048ee0:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8048ee5:	eb 05                	jmp    8048eec <fun7+0x4d>
 8048ee7:	b8 00 00 00 00       	mov    $0x0,%eax
 8048eec:	83 c4 1c             	add    $0x1c,%esp
 8048eef:	c3                   	ret

08048ef0 <secret_phase>:
 8048ef0:	53                   	push   %ebx
 8048ef1:	83 ec 18             	sub    $0x18,%esp
 8048ef4:	e8 49 03 00 00       	call   8049242 <read_line>
 8048ef9:	c7 44 24 08 0a 00 00 	movl   $0xa,0x8(%esp)
 8048f00:	00
 8048f01:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 8048f08:	00
 8048f09:	89 04 24             	mov    %eax,(%esp)
 8048f0c:	e8 cf f9 ff ff       	call   80488e0 <strtol@plt>
 8048f11:	89 c3                	mov    %eax,%ebx
 8048f13:	e8 5a 0d 00 00       	call   8049c72 <phase_init>
 8048f18:	8d 43 ff             	lea    -0x1(%ebx),%eax
 8048f1b:	3d e8 03 00 00       	cmp    $0x3e8,%eax
 8048f20:	76 05                	jbe    8048f27 <secret_phase+0x37>
 8048f22:	e8 e8 02 00 00       	call   804920f <explode_bomb>
 8048f27:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8048f2b:	c7 04 24 a0 c0 04 08 	movl   $0x804c0a0,(%esp)
 8048f32:	e8 68 ff ff ff       	call   8048e9f <fun7>
 8048f37:	83 f8 03             	cmp    $0x3,%eax
 8048f3a:	74 05                	je     8048f41 <secret_phase+0x51>
 8048f3c:	e8 ce 02 00 00       	call   804920f <explode_bomb>
 8048f41:	c7 04 24 18 a0 04 08 	movl   $0x804a018,(%esp)
 8048f48:	e8 b3 f8 ff ff       	call   8048800 <puts@plt>
 8048f4d:	e8 35 04 00 00       	call   8049387 <phase_defused>
 8048f52:	83 c4 18             	add    $0x18,%esp
 8048f55:	5b                   	pop    %ebx
 8048f56:	c3                   	ret
 8048f57:	90                   	nop

08048f58 <sig_handler>:
 8048f58:	83 ec 1c             	sub    $0x1c,%esp
 8048f5b:	c7 04 24 c0 a0 04 08 	movl   $0x804a0c0,(%esp)
 8048f62:	e8 99 f8 ff ff       	call   8048800 <puts@plt>
 8048f67:	83 c4 1c             	add    $0x1c,%esp
 8048f6a:	c3                   	ret

08048f6b <invalid_phase>:
 8048f6b:	83 ec 1c             	sub    $0x1c,%esp
 8048f6e:	8b 44 24 20          	mov    0x20(%esp),%eax
 8048f72:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048f76:	c7 44 24 04 0d a2 04 	movl   $0x804a20d,0x4(%esp)
 8048f7d:	08
 8048f7e:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048f85:	e8 16 f9 ff ff       	call   80488a0 <__printf_chk@plt>
 8048f8a:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048f91:	e8 aa f8 ff ff       	call   8048840 <exit@plt>

08048f96 <string_length>:
 8048f96:	8b 54 24 04          	mov    0x4(%esp),%edx
 8048f9a:	80 3a 00             	cmpb   $0x0,(%edx)
 8048f9d:	74 0d                	je     8048fac <string_length+0x16>
 8048f9f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048fa4:	40                   	inc    %eax
 8048fa5:	80 3c 02 00          	cmpb   $0x0,(%edx,%eax,1)
 8048fa9:	75 f9                	jne    8048fa4 <string_length+0xe>
 8048fab:	c3                   	ret
 8048fac:	b8 00 00 00 00       	mov    $0x0,%eax
 8048fb1:	c3                   	ret

08048fb2 <strings_not_equal>:
 8048fb2:	57                   	push   %edi
 8048fb3:	56                   	push   %esi
 8048fb4:	53                   	push   %ebx
 8048fb5:	83 ec 04             	sub    $0x4,%esp
 8048fb8:	8b 5c 24 14          	mov    0x14(%esp),%ebx
 8048fbc:	8b 74 24 18          	mov    0x18(%esp),%esi
 8048fc0:	89 1c 24             	mov    %ebx,(%esp)
 8048fc3:	e8 ce ff ff ff       	call   8048f96 <string_length>
 8048fc8:	89 c7                	mov    %eax,%edi
 8048fca:	89 34 24             	mov    %esi,(%esp)
 8048fcd:	e8 c4 ff ff ff       	call   8048f96 <string_length>
 8048fd2:	39 c7                	cmp    %eax,%edi
 8048fd4:	75 26                	jne    8048ffc <strings_not_equal+0x4a>
 8048fd6:	8a 03                	mov    (%ebx),%al
 8048fd8:	84 c0                	test   %al,%al
 8048fda:	74 27                	je     8049003 <strings_not_equal+0x51>
 8048fdc:	3a 06                	cmp    (%esi),%al
 8048fde:	75 2a                	jne    804900a <strings_not_equal+0x58>
 8048fe0:	b8 00 00 00 00       	mov    $0x0,%eax
 8048fe5:	eb 06                	jmp    8048fed <strings_not_equal+0x3b>
 8048fe7:	40                   	inc    %eax
 8048fe8:	3a 14 06             	cmp    (%esi,%eax,1),%dl
 8048feb:	75 24                	jne    8049011 <strings_not_equal+0x5f>
 8048fed:	8a 54 03 01          	mov    0x1(%ebx,%eax,1),%dl
 8048ff1:	84 d2                	test   %dl,%dl
 8048ff3:	75 f2                	jne    8048fe7 <strings_not_equal+0x35>
 8048ff5:	b8 00 00 00 00       	mov    $0x0,%eax
 8048ffa:	eb 1a                	jmp    8049016 <strings_not_equal+0x64>
 8048ffc:	b8 01 00 00 00       	mov    $0x1,%eax
 8049001:	eb 13                	jmp    8049016 <strings_not_equal+0x64>
 8049003:	b8 00 00 00 00       	mov    $0x0,%eax
 8049008:	eb 0c                	jmp    8049016 <strings_not_equal+0x64>
 804900a:	b8 01 00 00 00       	mov    $0x1,%eax
 804900f:	eb 05                	jmp    8049016 <strings_not_equal+0x64>
 8049011:	b8 01 00 00 00       	mov    $0x1,%eax
 8049016:	83 c4 04             	add    $0x4,%esp
 8049019:	5b                   	pop    %ebx
 804901a:	5e                   	pop    %esi
 804901b:	5f                   	pop    %edi
 804901c:	c3                   	ret

0804901d <initialize_bomb>:
 804901d:	81 ec 5c 20 00 00    	sub    $0x205c,%esp
 8049023:	c7 44 24 04 58 8f 04 	movl   $0x8048f58,0x4(%esp)
 804902a:	08
 804902b:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 8049032:	e8 79 f7 ff ff       	call   80487b0 <signal@plt>
 8049037:	c7 44 24 04 40 00 00 	movl   $0x40,0x4(%esp)
 804903e:	00
 804903f:	8d 84 24 10 20 00 00 	lea    0x2010(%esp),%eax
 8049046:	89 04 24             	mov    %eax,(%esp)
 8049049:	e8 92 f7 ff ff       	call   80487e0 <gethostname@plt>
 804904e:	85 c0                	test   %eax,%eax
 8049050:	74 18                	je     804906a <initialize_bomb+0x4d>
 8049052:	c7 04 24 e4 a0 04 08 	movl   $0x804a0e4,(%esp)
 8049059:	e8 a2 f7 ff ff       	call   8048800 <puts@plt>
 804905e:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049065:	e8 d6 f7 ff ff       	call   8048840 <exit@plt>
 804906a:	8d 44 24 10          	lea    0x10(%esp),%eax
 804906e:	89 04 24             	mov    %eax,(%esp)
 8049071:	e8 5c 0a 00 00       	call   8049ad2 <init_driver>
 8049076:	85 c0                	test   %eax,%eax
 8049078:	79 28                	jns    80490a2 <initialize_bomb+0x85>
 804907a:	8d 44 24 10          	lea    0x10(%esp),%eax
 804907e:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049082:	c7 44 24 04 1e a2 04 	movl   $0x804a21e,0x4(%esp)
 8049089:	08
 804908a:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8049091:	e8 0a f8 ff ff       	call   80488a0 <__printf_chk@plt>
 8049096:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 804909d:	e8 9e f7 ff ff       	call   8048840 <exit@plt>
 80490a2:	81 c4 5c 20 00 00    	add    $0x205c,%esp
 80490a8:	c3                   	ret

080490a9 <initialize_bomb_solve>:
 80490a9:	c3                   	ret

080490aa <blank_line>:
 80490aa:	56                   	push   %esi
 80490ab:	53                   	push   %ebx
 80490ac:	83 ec 04             	sub    $0x4,%esp
 80490af:	8b 74 24 10          	mov    0x10(%esp),%esi
 80490b3:	eb 12                	jmp    80490c7 <blank_line+0x1d>
 80490b5:	e8 56 f8 ff ff       	call   8048910 <__ctype_b_loc@plt>
 80490ba:	46                   	inc    %esi
 80490bb:	0f be db             	movsbl %bl,%ebx
 80490be:	8b 00                	mov    (%eax),%eax
 80490c0:	f6 44 58 01 20       	testb  $0x20,0x1(%eax,%ebx,2)
 80490c5:	74 0d                	je     80490d4 <blank_line+0x2a>
 80490c7:	8a 1e                	mov    (%esi),%bl
 80490c9:	84 db                	test   %bl,%bl
 80490cb:	75 e8                	jne    80490b5 <blank_line+0xb>
 80490cd:	b8 01 00 00 00       	mov    $0x1,%eax
 80490d2:	eb 05                	jmp    80490d9 <blank_line+0x2f>
 80490d4:	b8 00 00 00 00       	mov    $0x0,%eax
 80490d9:	83 c4 04             	add    $0x4,%esp
 80490dc:	5b                   	pop    %ebx
 80490dd:	5e                   	pop    %esi
 80490de:	c3                   	ret

080490df <skip>:
 80490df:	53                   	push   %ebx
 80490e0:	83 ec 18             	sub    $0x18,%esp
 80490e3:	a1 00 c8 04 08       	mov    0x804c800,%eax
 80490e8:	89 44 24 08          	mov    %eax,0x8(%esp)
 80490ec:	c7 44 24 04 50 00 00 	movl   $0x50,0x4(%esp)
 80490f3:	00
 80490f4:	a1 e0 c5 04 08       	mov    0x804c5e0,%eax
 80490f9:	8d 04 80             	lea    (%eax,%eax,4),%eax
 80490fc:	c1 e0 04             	shl    $0x4,%eax
 80490ff:	05 20 c8 04 08       	add    $0x804c820,%eax
 8049104:	89 04 24             	mov    %eax,(%esp)
 8049107:	e8 94 f6 ff ff       	call   80487a0 <fgets@plt>
 804910c:	89 c3                	mov    %eax,%ebx
 804910e:	85 c0                	test   %eax,%eax
 8049110:	74 0c                	je     804911e <skip+0x3f>
 8049112:	89 04 24             	mov    %eax,(%esp)
 8049115:	e8 90 ff ff ff       	call   80490aa <blank_line>
 804911a:	85 c0                	test   %eax,%eax
 804911c:	75 c5                	jne    80490e3 <skip+0x4>
 804911e:	89 d8                	mov    %ebx,%eax
 8049120:	83 c4 18             	add    $0x18,%esp
 8049123:	5b                   	pop    %ebx
 8049124:	c3                   	ret

08049125 <send_msg>:
 8049125:	57                   	push   %edi
 8049126:	53                   	push   %ebx
 8049127:	81 ec 24 40 00 00    	sub    $0x4024,%esp
 804912d:	8b 15 e0 c5 04 08    	mov    0x804c5e0,%edx
 8049133:	8d 5c 92 fb          	lea    -0x5(%edx,%edx,4),%ebx
 8049137:	c1 e3 04             	shl    $0x4,%ebx
 804913a:	81 c3 20 c8 04 08    	add    $0x804c820,%ebx
 8049140:	89 df                	mov    %ebx,%edi
 8049142:	b0 00                	mov    $0x0,%al
 8049144:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049149:	f2 ae                	repnz scas %es:(%edi),%al
 804914b:	f7 d1                	not    %ecx
 804914d:	83 c1 63             	add    $0x63,%ecx
 8049150:	81 f9 00 20 00 00    	cmp    $0x2000,%ecx
 8049156:	76 20                	jbe    8049178 <send_msg+0x53>
 8049158:	c7 44 24 04 1c a1 04 	movl   $0x804a11c,0x4(%esp)
 804915f:	08
 8049160:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8049167:	e8 34 f7 ff ff       	call   80488a0 <__printf_chk@plt>
 804916c:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049173:	e8 c8 f6 ff ff       	call   8048840 <exit@plt>
 8049178:	83 bc 24 30 40 00 00 	cmpl   $0x0,0x4030(%esp)
 804917f:	00
 8049180:	74 07                	je     8049189 <send_msg+0x64>
 8049182:	b8 38 a2 04 08       	mov    $0x804a238,%eax
 8049187:	eb 05                	jmp    804918e <send_msg+0x69>
 8049189:	b8 40 a2 04 08       	mov    $0x804a240,%eax
 804918e:	89 5c 24 1c          	mov    %ebx,0x1c(%esp)
 8049192:	89 54 24 18          	mov    %edx,0x18(%esp)
 8049196:	89 44 24 14          	mov    %eax,0x14(%esp)
 804919a:	a1 a0 c5 04 08       	mov    0x804c5a0,%eax
 804919f:	89 44 24 10          	mov    %eax,0x10(%esp)
 80491a3:	c7 44 24 0c 49 a2 04 	movl   $0x804a249,0xc(%esp)
 80491aa:	08
 80491ab:	c7 44 24 08 00 20 00 	movl   $0x2000,0x8(%esp)
 80491b2:	00
 80491b3:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 80491ba:	00
 80491bb:	8d 9c 24 20 20 00 00 	lea    0x2020(%esp),%ebx
 80491c2:	89 1c 24             	mov    %ebx,(%esp)
 80491c5:	e8 56 f7 ff ff       	call   8048920 <__sprintf_chk@plt>
 80491ca:	8d 44 24 20          	lea    0x20(%esp),%eax
 80491ce:	89 44 24 0c          	mov    %eax,0xc(%esp)
 80491d2:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 80491d9:	00
 80491da:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 80491de:	c7 04 24 a0 c1 04 08 	movl   $0x804c1a0,(%esp)
 80491e5:	e8 53 0b 00 00       	call   8049d3d <driver_post>
 80491ea:	85 c0                	test   %eax,%eax
 80491ec:	79 18                	jns    8049206 <send_msg+0xe1>
 80491ee:	8d 44 24 20          	lea    0x20(%esp),%eax
 80491f2:	89 04 24             	mov    %eax,(%esp)
 80491f5:	e8 06 f6 ff ff       	call   8048800 <puts@plt>
 80491fa:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8049201:	e8 3a f6 ff ff       	call   8048840 <exit@plt>
 8049206:	81 c4 24 40 00 00    	add    $0x4024,%esp
 804920c:	5b                   	pop    %ebx
 804920d:	5f                   	pop    %edi
 804920e:	c3                   	ret

0804920f <explode_bomb>:
 804920f:	83 ec 1c             	sub    $0x1c,%esp
 8049212:	c7 04 24 55 a2 04 08 	movl   $0x804a255,(%esp)
 8049219:	e8 e2 f5 ff ff       	call   8048800 <puts@plt>
 804921e:	c7 04 24 5e a2 04 08 	movl   $0x804a25e,(%esp)
 8049225:	e8 d6 f5 ff ff       	call   8048800 <puts@plt>
 804922a:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8049231:	90                   	nop
 8049232:	90                   	nop
 8049233:	90                   	nop
 8049234:	90                   	nop
 8049235:	90                   	nop
 8049236:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 804923d:	e8 fe f5 ff ff       	call   8048840 <exit@plt>

08049242 <read_line>:
 8049242:	57                   	push   %edi
 8049243:	56                   	push   %esi
 8049244:	53                   	push   %ebx
 8049245:	83 ec 20             	sub    $0x20,%esp
 8049248:	e8 92 fe ff ff       	call   80490df <skip>
 804924d:	85 c0                	test   %eax,%eax
 804924f:	75 6c                	jne    80492bd <read_line+0x7b>
 8049251:	a1 c4 c5 04 08       	mov    0x804c5c4,%eax
 8049256:	39 05 00 c8 04 08    	cmp    %eax,0x804c800
 804925c:	75 18                	jne    8049276 <read_line+0x34>
 804925e:	c7 04 24 75 a2 04 08 	movl   $0x804a275,(%esp)
 8049265:	e8 96 f5 ff ff       	call   8048800 <puts@plt>
 804926a:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049271:	e8 ca f5 ff ff       	call   8048840 <exit@plt>
 8049276:	c7 04 24 93 a2 04 08 	movl   $0x804a293,(%esp)
 804927d:	e8 6e f5 ff ff       	call   80487f0 <getenv@plt>
 8049282:	85 c0                	test   %eax,%eax
 8049284:	74 0c                	je     8049292 <read_line+0x50>
 8049286:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 804928d:	e8 ae f5 ff ff       	call   8048840 <exit@plt>
 8049292:	a1 c4 c5 04 08       	mov    0x804c5c4,%eax
 8049297:	a3 00 c8 04 08       	mov    %eax,0x804c800
 804929c:	e8 3e fe ff ff       	call   80490df <skip>
 80492a1:	85 c0                	test   %eax,%eax
 80492a3:	75 18                	jne    80492bd <read_line+0x7b>
 80492a5:	c7 04 24 75 a2 04 08 	movl   $0x804a275,(%esp)
 80492ac:	e8 4f f5 ff ff       	call   8048800 <puts@plt>
 80492b1:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 80492b8:	e8 83 f5 ff ff       	call   8048840 <exit@plt>
 80492bd:	8b 15 e0 c5 04 08    	mov    0x804c5e0,%edx
 80492c3:	8d 1c 92             	lea    (%edx,%edx,4),%ebx
 80492c6:	c1 e3 04             	shl    $0x4,%ebx
 80492c9:	81 c3 20 c8 04 08    	add    $0x804c820,%ebx
 80492cf:	89 df                	mov    %ebx,%edi
 80492d1:	b0 00                	mov    $0x0,%al
 80492d3:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 80492d8:	f2 ae                	repnz scas %es:(%edi),%al
 80492da:	f7 d1                	not    %ecx
 80492dc:	49                   	dec    %ecx
 80492dd:	83 f9 4e             	cmp    $0x4e,%ecx
 80492e0:	7e 37                	jle    8049319 <read_line+0xd7>
 80492e2:	c7 04 24 9e a2 04 08 	movl   $0x804a29e,(%esp)
 80492e9:	e8 12 f5 ff ff       	call   8048800 <puts@plt>
 80492ee:	a1 e0 c5 04 08       	mov    0x804c5e0,%eax
 80492f3:	8d 50 01             	lea    0x1(%eax),%edx
 80492f6:	89 15 e0 c5 04 08    	mov    %edx,0x804c5e0
 80492fc:	6b c0 50             	imul   $0x50,%eax,%eax
 80492ff:	05 20 c8 04 08       	add    $0x804c820,%eax
 8049304:	ba b9 a2 04 08       	mov    $0x804a2b9,%edx
 8049309:	b9 04 00 00 00       	mov    $0x4,%ecx
 804930e:	89 c7                	mov    %eax,%edi
 8049310:	89 d6                	mov    %edx,%esi
 8049312:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049314:	e8 f6 fe ff ff       	call   804920f <explode_bomb>
 8049319:	8d 04 92             	lea    (%edx,%edx,4),%eax
 804931c:	c1 e0 04             	shl    $0x4,%eax
 804931f:	c6 84 01 1f c8 04 08 	movb   $0x0,0x804c81f(%ecx,%eax,1)
 8049326:	00
 8049327:	42                   	inc    %edx
 8049328:	89 15 e0 c5 04 08    	mov    %edx,0x804c5e0
 804932e:	89 d8                	mov    %ebx,%eax
 8049330:	83 c4 20             	add    $0x20,%esp
 8049333:	5b                   	pop    %ebx
 8049334:	5e                   	pop    %esi
 8049335:	5f                   	pop    %edi
 8049336:	c3                   	ret

08049337 <read_six_numbers>:
 8049337:	83 ec 2c             	sub    $0x2c,%esp
 804933a:	8b 44 24 34          	mov    0x34(%esp),%eax
 804933e:	8d 50 14             	lea    0x14(%eax),%edx
 8049341:	89 54 24 1c          	mov    %edx,0x1c(%esp)
 8049345:	8d 50 10             	lea    0x10(%eax),%edx
 8049348:	89 54 24 18          	mov    %edx,0x18(%esp)
 804934c:	8d 50 0c             	lea    0xc(%eax),%edx
 804934f:	89 54 24 14          	mov    %edx,0x14(%esp)
 8049353:	8d 50 08             	lea    0x8(%eax),%edx
 8049356:	89 54 24 10          	mov    %edx,0x10(%esp)
 804935a:	8d 50 04             	lea    0x4(%eax),%edx
 804935d:	89 54 24 0c          	mov    %edx,0xc(%esp)
 8049361:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049365:	c7 44 24 04 c9 a2 04 	movl   $0x804a2c9,0x4(%esp)
 804936c:	08
 804936d:	8b 44 24 30          	mov    0x30(%esp),%eax
 8049371:	89 04 24             	mov    %eax,(%esp)
 8049374:	e8 f7 f4 ff ff       	call   8048870 <__isoc99_sscanf@plt>
 8049379:	83 f8 05             	cmp    $0x5,%eax
 804937c:	7f 05                	jg     8049383 <read_six_numbers+0x4c>
 804937e:	e8 8c fe ff ff       	call   804920f <explode_bomb>
 8049383:	83 c4 2c             	add    $0x2c,%esp
 8049386:	c3                   	ret

08049387 <phase_defused>:
 8049387:	81 ec 8c 00 00 00    	sub    $0x8c,%esp
 804938d:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8049394:	e8 8c fd ff ff       	call   8049125 <send_msg>
 8049399:	83 3d e0 c5 04 08 06 	cmpl   $0x6,0x804c5e0
 80493a0:	75 7e                	jne    8049420 <phase_defused+0x99>
 80493a2:	8d 44 24 30          	lea    0x30(%esp),%eax
 80493a6:	89 44 24 10          	mov    %eax,0x10(%esp)
 80493aa:	8d 44 24 28          	lea    0x28(%esp),%eax
 80493ae:	89 44 24 0c          	mov    %eax,0xc(%esp)
 80493b2:	8d 44 24 2c          	lea    0x2c(%esp),%eax
 80493b6:	89 44 24 08          	mov    %eax,0x8(%esp)
 80493ba:	c7 44 24 04 db a2 04 	movl   $0x804a2db,0x4(%esp)
 80493c1:	08
 80493c2:	c7 04 24 10 c9 04 08 	movl   $0x804c910,(%esp)
 80493c9:	e8 a2 f4 ff ff       	call   8048870 <__isoc99_sscanf@plt>
 80493ce:	83 f8 03             	cmp    $0x3,%eax
 80493d1:	75 35                	jne    8049408 <phase_defused+0x81>
 80493d3:	c7 44 24 04 e4 a2 04 	movl   $0x804a2e4,0x4(%esp)
 80493da:	08
 80493db:	8d 44 24 30          	lea    0x30(%esp),%eax
 80493df:	89 04 24             	mov    %eax,(%esp)
 80493e2:	e8 cb fb ff ff       	call   8048fb2 <strings_not_equal>
 80493e7:	85 c0                	test   %eax,%eax
 80493e9:	75 1d                	jne    8049408 <phase_defused+0x81>
 80493eb:	c7 04 24 40 a1 04 08 	movl   $0x804a140,(%esp)
 80493f2:	e8 09 f4 ff ff       	call   8048800 <puts@plt>
 80493f7:	c7 04 24 68 a1 04 08 	movl   $0x804a168,(%esp)
 80493fe:	e8 fd f3 ff ff       	call   8048800 <puts@plt>
 8049403:	e8 e8 fa ff ff       	call   8048ef0 <secret_phase>
 8049408:	c7 04 24 a0 a1 04 08 	movl   $0x804a1a0,(%esp)
 804940f:	e8 ec f3 ff ff       	call   8048800 <puts@plt>
 8049414:	c7 04 24 cc a1 04 08 	movl   $0x804a1cc,(%esp)
 804941b:	e8 e0 f3 ff ff       	call   8048800 <puts@plt>
 8049420:	81 c4 8c 00 00 00    	add    $0x8c,%esp
 8049426:	c3                   	ret
 8049427:	90                   	nop

08049428 <rio_readlineb>:
 8049428:	55                   	push   %ebp
 8049429:	57                   	push   %edi
 804942a:	56                   	push   %esi
 804942b:	53                   	push   %ebx
 804942c:	83 ec 3c             	sub    $0x3c,%esp
 804942f:	89 c3                	mov    %eax,%ebx
 8049431:	83 f9 01             	cmp    $0x1,%ecx
 8049434:	0f 86 b0 00 00 00    	jbe    80494ea <rio_readlineb+0xc2>
 804943a:	89 4c 24 1c          	mov    %ecx,0x1c(%esp)
 804943e:	89 d5                	mov    %edx,%ebp
 8049440:	c7 44 24 18 01 00 00 	movl   $0x1,0x18(%esp)
 8049447:	00
 8049448:	8d 78 0c             	lea    0xc(%eax),%edi
 804944b:	eb 37                	jmp    8049484 <rio_readlineb+0x5c>
 804944d:	c7 44 24 08 00 20 00 	movl   $0x2000,0x8(%esp)
 8049454:	00
 8049455:	89 7c 24 04          	mov    %edi,0x4(%esp)
 8049459:	8b 03                	mov    (%ebx),%eax
 804945b:	89 04 24             	mov    %eax,(%esp)
 804945e:	e8 2d f3 ff ff       	call   8048790 <read@plt>
 8049463:	89 43 04             	mov    %eax,0x4(%ebx)
 8049466:	85 c0                	test   %eax,%eax
 8049468:	79 0f                	jns    8049479 <rio_readlineb+0x51>
 804946a:	e8 21 f4 ff ff       	call   8048890 <__errno_location@plt>
 804946f:	83 38 04             	cmpl   $0x4,(%eax)
 8049472:	74 10                	je     8049484 <rio_readlineb+0x5c>
 8049474:	e9 9f 00 00 00       	jmp    8049518 <rio_readlineb+0xf0>
 8049479:	85 c0                	test   %eax,%eax
 804947b:	0f 84 9e 00 00 00    	je     804951f <rio_readlineb+0xf7>
 8049481:	89 7b 08             	mov    %edi,0x8(%ebx)
 8049484:	8b 73 04             	mov    0x4(%ebx),%esi
 8049487:	85 f6                	test   %esi,%esi
 8049489:	7e c2                	jle    804944d <rio_readlineb+0x25>
 804948b:	85 f6                	test   %esi,%esi
 804948d:	0f 85 97 00 00 00    	jne    804952a <rio_readlineb+0x102>
 8049493:	c7 44 24 0c 01 00 00 	movl   $0x1,0xc(%esp)
 804949a:	00
 804949b:	89 74 24 08          	mov    %esi,0x8(%esp)
 804949f:	8b 43 08             	mov    0x8(%ebx),%eax
 80494a2:	89 44 24 04          	mov    %eax,0x4(%esp)
 80494a6:	8d 44 24 2f          	lea    0x2f(%esp),%eax
 80494aa:	89 04 24             	mov    %eax,(%esp)
 80494ad:	e8 6e f3 ff ff       	call   8048820 <__memcpy_chk@plt>
 80494b2:	01 73 08             	add    %esi,0x8(%ebx)
 80494b5:	29 73 04             	sub    %esi,0x4(%ebx)
 80494b8:	83 fe 01             	cmp    $0x1,%esi
 80494bb:	75 0e                	jne    80494cb <rio_readlineb+0xa3>
 80494bd:	8a 44 24 2f          	mov    0x2f(%esp),%al
 80494c1:	88 45 00             	mov    %al,0x0(%ebp)
 80494c4:	45                   	inc    %ebp
 80494c5:	3c 0a                	cmp    $0xa,%al
 80494c7:	75 11                	jne    80494da <rio_readlineb+0xb2>
 80494c9:	eb 29                	jmp    80494f4 <rio_readlineb+0xcc>
 80494cb:	8b 44 24 18          	mov    0x18(%esp),%eax
 80494cf:	85 f6                	test   %esi,%esi
 80494d1:	75 27                	jne    80494fa <rio_readlineb+0xd2>
 80494d3:	83 f8 01             	cmp    $0x1,%eax
 80494d6:	75 1c                	jne    80494f4 <rio_readlineb+0xcc>
 80494d8:	eb 2a                	jmp    8049504 <rio_readlineb+0xdc>
 80494da:	ff 44 24 18          	incl   0x18(%esp)
 80494de:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 80494e2:	39 44 24 18          	cmp    %eax,0x18(%esp)
 80494e6:	75 9c                	jne    8049484 <rio_readlineb+0x5c>
 80494e8:	eb 0a                	jmp    80494f4 <rio_readlineb+0xcc>
 80494ea:	89 d5                	mov    %edx,%ebp
 80494ec:	c7 44 24 18 01 00 00 	movl   $0x1,0x18(%esp)
 80494f3:	00
 80494f4:	c6 45 00 00          	movb   $0x0,0x0(%ebp)
 80494f8:	eb 12                	jmp    804950c <rio_readlineb+0xe4>
 80494fa:	c7 44 24 18 ff ff ff 	movl   $0xffffffff,0x18(%esp)
 8049501:	ff
 8049502:	eb 08                	jmp    804950c <rio_readlineb+0xe4>
 8049504:	c7 44 24 18 00 00 00 	movl   $0x0,0x18(%esp)
 804950b:	00
 804950c:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049510:	83 c4 3c             	add    $0x3c,%esp
 8049513:	5b                   	pop    %ebx
 8049514:	5e                   	pop    %esi
 8049515:	5f                   	pop    %edi
 8049516:	5d                   	pop    %ebp
 8049517:	c3                   	ret
 8049518:	be ff ff ff ff       	mov    $0xffffffff,%esi
 804951d:	eb 05                	jmp    8049524 <rio_readlineb+0xfc>
 804951f:	be 00 00 00 00       	mov    $0x0,%esi
 8049524:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049528:	eb a5                	jmp    80494cf <rio_readlineb+0xa7>
 804952a:	8b 43 08             	mov    0x8(%ebx),%eax
 804952d:	8a 00                	mov    (%eax),%al
 804952f:	88 44 24 2f          	mov    %al,0x2f(%esp)
 8049533:	ff 43 08             	incl   0x8(%ebx)
 8049536:	ff 4b 04             	decl   0x4(%ebx)
 8049539:	eb 82                	jmp    80494bd <rio_readlineb+0x95>

0804953b <sigalrm_handler>:
 804953b:	83 ec 1c             	sub    $0x1c,%esp
 804953e:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
 8049545:	00
 8049546:	c7 44 24 08 f0 a2 04 	movl   $0x804a2f0,0x8(%esp)
 804954d:	08
 804954e:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049555:	00
 8049556:	a1 c0 c5 04 08       	mov    0x804c5c0,%eax
 804955b:	89 04 24             	mov    %eax,(%esp)
 804955e:	e8 5d f3 ff ff       	call   80488c0 <__fprintf_chk@plt>
 8049563:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 804956a:	e8 d1 f2 ff ff       	call   8048840 <exit@plt>

0804956f <submitr>:
 804956f:	55                   	push   %ebp
 8049570:	57                   	push   %edi
 8049571:	56                   	push   %esi
 8049572:	53                   	push   %ebx
 8049573:	81 ec 6c a0 00 00    	sub    $0xa06c,%esp
 8049579:	8b b4 24 94 a0 00 00 	mov    0xa094(%esp),%esi
 8049580:	c7 84 24 40 20 00 00 	movl   $0x0,0x2040(%esp)
 8049587:	00 00 00 00
 804958b:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 8049592:	00
 8049593:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 804959a:	00
 804959b:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 80495a2:	e8 09 f3 ff ff       	call   80488b0 <socket@plt>
 80495a7:	89 c5                	mov    %eax,%ebp
 80495a9:	85 c0                	test   %eax,%eax
 80495ab:	79 1d                	jns    80495ca <submitr+0x5b>
 80495ad:	be 14 a3 04 08       	mov    $0x804a314,%esi
 80495b2:	b9 26 00 00 00       	mov    $0x26,%ecx
 80495b7:	8b bc 24 98 a0 00 00 	mov    0xa098(%esp),%edi
 80495be:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 80495c0:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80495c5:	e9 59 04 00 00       	jmp    8049a23 <submitr+0x4b4>
 80495ca:	8b 84 24 80 a0 00 00 	mov    0xa080(%esp),%eax
 80495d1:	89 04 24             	mov    %eax,(%esp)
 80495d4:	e8 f7 f2 ff ff       	call   80488d0 <gethostbyname@plt>
 80495d9:	89 c2                	mov    %eax,%edx
 80495db:	85 c0                	test   %eax,%eax
 80495dd:	75 25                	jne    8049604 <submitr+0x95>
 80495df:	be 3c a3 04 08       	mov    $0x804a33c,%esi
 80495e4:	b9 2f 00 00 00       	mov    $0x2f,%ecx
 80495e9:	8b bc 24 98 a0 00 00 	mov    0xa098(%esp),%edi
 80495f0:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 80495f2:	89 2c 24             	mov    %ebp,(%esp)
 80495f5:	e8 06 f3 ff ff       	call   8048900 <close@plt>
 80495fa:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80495ff:	e9 1f 04 00 00       	jmp    8049a23 <submitr+0x4b4>
 8049604:	8d 9c 24 50 a0 00 00 	lea    0xa050(%esp),%ebx
 804960b:	b9 10 00 00 00       	mov    $0x10,%ecx
 8049610:	b0 00                	mov    $0x0,%al
 8049612:	89 df                	mov    %ebx,%edi
 8049614:	f3 aa                	rep stos %al,%es:(%edi)
 8049616:	66 c7 84 24 50 a0 00 	movw   $0x2,0xa050(%esp)
 804961d:	00 02 00
 8049620:	c7 44 24 0c 0c 00 00 	movl   $0xc,0xc(%esp)
 8049627:	00
 8049628:	8b 42 0c             	mov    0xc(%edx),%eax
 804962b:	89 44 24 08          	mov    %eax,0x8(%esp)
 804962f:	8b 42 10             	mov    0x10(%edx),%eax
 8049632:	8b 00                	mov    (%eax),%eax
 8049634:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049638:	8d 84 24 54 a0 00 00 	lea    0xa054(%esp),%eax
 804963f:	89 04 24             	mov    %eax,(%esp)
 8049642:	e8 c9 f1 ff ff       	call   8048810 <__memmove_chk@plt>
 8049647:	8b 84 24 84 a0 00 00 	mov    0xa084(%esp),%eax
 804964e:	66 c1 c8 08          	ror    $0x8,%ax
 8049652:	66 89 84 24 52 a0 00 	mov    %ax,0xa052(%esp)
 8049659:	00
 804965a:	c7 44 24 08 10 00 00 	movl   $0x10,0x8(%esp)
 8049661:	00
 8049662:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8049666:	89 2c 24             	mov    %ebp,(%esp)
 8049669:	e8 82 f2 ff ff       	call   80488f0 <connect@plt>
 804966e:	85 c0                	test   %eax,%eax
 8049670:	79 25                	jns    8049697 <submitr+0x128>
 8049672:	be 6c a3 04 08       	mov    $0x804a36c,%esi
 8049677:	b9 27 00 00 00       	mov    $0x27,%ecx
 804967c:	8b bc 24 98 a0 00 00 	mov    0xa098(%esp),%edi
 8049683:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 8049685:	89 2c 24             	mov    %ebp,(%esp)
 8049688:	e8 73 f2 ff ff       	call   8048900 <close@plt>
 804968d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049692:	e9 8c 03 00 00       	jmp    8049a23 <submitr+0x4b4>
 8049697:	ba ff ff ff ff       	mov    $0xffffffff,%edx
 804969c:	89 f7                	mov    %esi,%edi
 804969e:	b0 00                	mov    $0x0,%al
 80496a0:	89 d1                	mov    %edx,%ecx
 80496a2:	f2 ae                	repnz scas %es:(%edi),%al
 80496a4:	89 cb                	mov    %ecx,%ebx
 80496a6:	f7 d3                	not    %ebx
 80496a8:	8b bc 24 88 a0 00 00 	mov    0xa088(%esp),%edi
 80496af:	89 d1                	mov    %edx,%ecx
 80496b1:	f2 ae                	repnz scas %es:(%edi),%al
 80496b3:	89 4c 24 28          	mov    %ecx,0x28(%esp)
 80496b7:	8b bc 24 8c a0 00 00 	mov    0xa08c(%esp),%edi
 80496be:	89 d1                	mov    %edx,%ecx
 80496c0:	f2 ae                	repnz scas %es:(%edi),%al
 80496c2:	f7 d1                	not    %ecx
 80496c4:	89 4c 24 2c          	mov    %ecx,0x2c(%esp)
 80496c8:	8b bc 24 90 a0 00 00 	mov    0xa090(%esp),%edi
 80496cf:	89 d1                	mov    %edx,%ecx
 80496d1:	f2 ae                	repnz scas %es:(%edi),%al
 80496d3:	89 ca                	mov    %ecx,%edx
 80496d5:	8b 4c 24 2c          	mov    0x2c(%esp),%ecx
 80496d9:	2b 4c 24 28          	sub    0x28(%esp),%ecx
 80496dd:	29 d1                	sub    %edx,%ecx
 80496df:	8d 44 5b fd          	lea    -0x3(%ebx,%ebx,2),%eax
 80496e3:	8d 44 01 7b          	lea    0x7b(%ecx,%eax,1),%eax
 80496e7:	3d 00 20 00 00       	cmp    $0x2000,%eax
 80496ec:	76 25                	jbe    8049713 <submitr+0x1a4>
 80496ee:	be 94 a3 04 08       	mov    $0x804a394,%esi
 80496f3:	b9 0e 00 00 00       	mov    $0xe,%ecx
 80496f8:	8b bc 24 98 a0 00 00 	mov    0xa098(%esp),%edi
 80496ff:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049701:	89 2c 24             	mov    %ebp,(%esp)
 8049704:	e8 f7 f1 ff ff       	call   8048900 <close@plt>
 8049709:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804970e:	e9 10 03 00 00       	jmp    8049a23 <submitr+0x4b4>
 8049713:	8d 94 24 44 40 00 00 	lea    0x4044(%esp),%edx
 804971a:	b0 00                	mov    $0x0,%al
 804971c:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049721:	89 d7                	mov    %edx,%edi
 8049723:	f3 aa                	rep stos %al,%es:(%edi)
 8049725:	89 f7                	mov    %esi,%edi
 8049727:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 804972c:	f2 ae                	repnz scas %es:(%edi),%al
 804972e:	f7 d1                	not    %ecx
 8049730:	89 cf                	mov    %ecx,%edi
 8049732:	4f                   	dec    %edi
 8049733:	0f 84 f5 02 00 00    	je     8049a2e <submitr+0x4bf>
 8049739:	89 d3                	mov    %edx,%ebx
 804973b:	8a 06                	mov    (%esi),%al
 804973d:	3c 2a                	cmp    $0x2a,%al
 804973f:	74 24                	je     8049765 <submitr+0x1f6>
 8049741:	3c 2d                	cmp    $0x2d,%al
 8049743:	74 20                	je     8049765 <submitr+0x1f6>
 8049745:	3c 2e                	cmp    $0x2e,%al
 8049747:	74 1c                	je     8049765 <submitr+0x1f6>
 8049749:	3c 5f                	cmp    $0x5f,%al
 804974b:	74 18                	je     8049765 <submitr+0x1f6>
 804974d:	8d 50 d0             	lea    -0x30(%eax),%edx
 8049750:	80 fa 09             	cmp    $0x9,%dl
 8049753:	76 10                	jbe    8049765 <submitr+0x1f6>
 8049755:	8d 50 bf             	lea    -0x41(%eax),%edx
 8049758:	80 fa 19             	cmp    $0x19,%dl
 804975b:	76 08                	jbe    8049765 <submitr+0x1f6>
 804975d:	8d 50 9f             	lea    -0x61(%eax),%edx
 8049760:	80 fa 19             	cmp    $0x19,%dl
 8049763:	77 05                	ja     804976a <submitr+0x1fb>
 8049765:	88 03                	mov    %al,(%ebx)
 8049767:	43                   	inc    %ebx
 8049768:	eb 58                	jmp    80497c2 <submitr+0x253>
 804976a:	3c 20                	cmp    $0x20,%al
 804976c:	75 06                	jne    8049774 <submitr+0x205>
 804976e:	c6 03 2b             	movb   $0x2b,(%ebx)
 8049771:	43                   	inc    %ebx
 8049772:	eb 4e                	jmp    80497c2 <submitr+0x253>
 8049774:	8d 50 e0             	lea    -0x20(%eax),%edx
 8049777:	80 fa 5f             	cmp    $0x5f,%dl
 804977a:	76 04                	jbe    8049780 <submitr+0x211>
 804977c:	3c 09                	cmp    $0x9,%al
 804977e:	75 4f                	jne    80497cf <submitr+0x260>
 8049780:	0f b6 c0             	movzbl %al,%eax
 8049783:	89 44 24 10          	mov    %eax,0x10(%esp)
 8049787:	c7 44 24 0c e0 a5 04 	movl   $0x804a5e0,0xc(%esp)
 804978e:	08
 804978f:	c7 44 24 08 08 00 00 	movl   $0x8,0x8(%esp)
 8049796:	00
 8049797:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 804979e:	00
 804979f:	8d 44 24 38          	lea    0x38(%esp),%eax
 80497a3:	89 04 24             	mov    %eax,(%esp)
 80497a6:	e8 75 f1 ff ff       	call   8048920 <__sprintf_chk@plt>
 80497ab:	8a 44 24 38          	mov    0x38(%esp),%al
 80497af:	88 03                	mov    %al,(%ebx)
 80497b1:	8a 44 24 39          	mov    0x39(%esp),%al
 80497b5:	88 43 01             	mov    %al,0x1(%ebx)
 80497b8:	8a 44 24 3a          	mov    0x3a(%esp),%al
 80497bc:	88 43 02             	mov    %al,0x2(%ebx)
 80497bf:	83 c3 03             	add    $0x3,%ebx
 80497c2:	46                   	inc    %esi
 80497c3:	4f                   	dec    %edi
 80497c4:	0f 85 71 ff ff ff    	jne    804973b <submitr+0x1cc>
 80497ca:	e9 5f 02 00 00       	jmp    8049a2e <submitr+0x4bf>
 80497cf:	be cc a3 04 08       	mov    $0x804a3cc,%esi
 80497d4:	b9 43 00 00 00       	mov    $0x43,%ecx
 80497d9:	8b bc 24 98 a0 00 00 	mov    0xa098(%esp),%edi
 80497e0:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 80497e2:	89 2c 24             	mov    %ebp,(%esp)
 80497e5:	e8 16 f1 ff ff       	call   8048900 <close@plt>
 80497ea:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80497ef:	e9 2f 02 00 00       	jmp    8049a23 <submitr+0x4b4>
 80497f4:	89 fb                	mov    %edi,%ebx
 80497f6:	8d b4 24 44 60 00 00 	lea    0x6044(%esp),%esi
 80497fd:	89 5c 24 08          	mov    %ebx,0x8(%esp)
 8049801:	89 74 24 04          	mov    %esi,0x4(%esp)
 8049805:	89 2c 24             	mov    %ebp,(%esp)
 8049808:	e8 53 f0 ff ff       	call   8048860 <write@plt>
 804980d:	85 c0                	test   %eax,%eax
 804980f:	7f 0f                	jg     8049820 <submitr+0x2b1>
 8049811:	e8 7a f0 ff ff       	call   8048890 <__errno_location@plt>
 8049816:	83 38 04             	cmpl   $0x4,(%eax)
 8049819:	75 0f                	jne    804982a <submitr+0x2bb>
 804981b:	b8 00 00 00 00       	mov    $0x0,%eax
 8049820:	01 c6                	add    %eax,%esi
 8049822:	29 c3                	sub    %eax,%ebx
 8049824:	75 d7                	jne    80497fd <submitr+0x28e>
 8049826:	85 ff                	test   %edi,%edi
 8049828:	79 25                	jns    804984f <submitr+0x2e0>
 804982a:	be 10 a4 04 08       	mov    $0x804a410,%esi
 804982f:	b9 0b 00 00 00       	mov    $0xb,%ecx
 8049834:	8b bc 24 98 a0 00 00 	mov    0xa098(%esp),%edi
 804983b:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 804983d:	89 2c 24             	mov    %ebp,(%esp)
 8049840:	e8 bb f0 ff ff       	call   8048900 <close@plt>
 8049845:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804984a:	e9 d4 01 00 00       	jmp    8049a23 <submitr+0x4b4>
 804984f:	89 ac 24 44 80 00 00 	mov    %ebp,0x8044(%esp)
 8049856:	c7 84 24 48 80 00 00 	movl   $0x0,0x8048(%esp)
 804985d:	00 00 00 00
 8049861:	8d 84 24 50 80 00 00 	lea    0x8050(%esp),%eax
 8049868:	89 84 24 4c 80 00 00 	mov    %eax,0x804c(%esp)
 804986f:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049874:	8d 94 24 44 60 00 00 	lea    0x6044(%esp),%edx
 804987b:	8d 84 24 44 80 00 00 	lea    0x8044(%esp),%eax
 8049882:	e8 a1 fb ff ff       	call   8049428 <rio_readlineb>
 8049887:	85 c0                	test   %eax,%eax
 8049889:	7f 25                	jg     80498b0 <submitr+0x341>
 804988b:	be 3c a4 04 08       	mov    $0x804a43c,%esi
 8049890:	b9 36 00 00 00       	mov    $0x36,%ecx
 8049895:	8b bc 24 98 a0 00 00 	mov    0xa098(%esp),%edi
 804989c:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 804989e:	89 2c 24             	mov    %ebp,(%esp)
 80498a1:	e8 5a f0 ff ff       	call   8048900 <close@plt>
 80498a6:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80498ab:	e9 73 01 00 00       	jmp    8049a23 <submitr+0x4b4>
 80498b0:	8d 44 24 40          	lea    0x40(%esp),%eax
 80498b4:	89 44 24 10          	mov    %eax,0x10(%esp)
 80498b8:	8d 84 24 40 20 00 00 	lea    0x2040(%esp),%eax
 80498bf:	89 44 24 0c          	mov    %eax,0xc(%esp)
 80498c3:	8d 84 24 44 20 00 00 	lea    0x2044(%esp),%eax
 80498ca:	89 44 24 08          	mov    %eax,0x8(%esp)
 80498ce:	c7 44 24 04 e7 a5 04 	movl   $0x804a5e7,0x4(%esp)
 80498d5:	08
 80498d6:	8d 84 24 44 60 00 00 	lea    0x6044(%esp),%eax
 80498dd:	89 04 24             	mov    %eax,(%esp)
 80498e0:	e8 8b ef ff ff       	call   8048870 <__isoc99_sscanf@plt>
 80498e5:	8b 84 24 40 20 00 00 	mov    0x2040(%esp),%eax
 80498ec:	3d c8 00 00 00       	cmp    $0xc8,%eax
 80498f1:	0f 84 86 00 00 00    	je     804997d <submitr+0x40e>
 80498f7:	8d 54 24 40          	lea    0x40(%esp),%edx
 80498fb:	89 54 24 14          	mov    %edx,0x14(%esp)
 80498ff:	89 44 24 10          	mov    %eax,0x10(%esp)
 8049903:	c7 44 24 0c 74 a4 04 	movl   $0x804a474,0xc(%esp)
 804990a:	08
 804990b:	c7 44 24 08 ff ff ff 	movl   $0xffffffff,0x8(%esp)
 8049912:	ff
 8049913:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 804991a:	00
 804991b:	8b 8c 24 98 a0 00 00 	mov    0xa098(%esp),%ecx
 8049922:	89 0c 24             	mov    %ecx,(%esp)
 8049925:	e8 f6 ef ff ff       	call   8048920 <__sprintf_chk@plt>
 804992a:	89 2c 24             	mov    %ebp,(%esp)
 804992d:	e8 ce ef ff ff       	call   8048900 <close@plt>
 8049932:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049937:	e9 e7 00 00 00       	jmp    8049a23 <submitr+0x4b4>
 804993c:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049941:	8d 94 24 44 60 00 00 	lea    0x6044(%esp),%edx
 8049948:	8d 84 24 44 80 00 00 	lea    0x8044(%esp),%eax
 804994f:	e8 d4 fa ff ff       	call   8049428 <rio_readlineb>
 8049954:	85 c0                	test   %eax,%eax
 8049956:	7f 25                	jg     804997d <submitr+0x40e>
 8049958:	be a4 a4 04 08       	mov    $0x804a4a4,%esi
 804995d:	b9 31 00 00 00       	mov    $0x31,%ecx
 8049962:	8b bc 24 98 a0 00 00 	mov    0xa098(%esp),%edi
 8049969:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 804996b:	89 2c 24             	mov    %ebp,(%esp)
 804996e:	e8 8d ef ff ff       	call   8048900 <close@plt>
 8049973:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049978:	e9 a6 00 00 00       	jmp    8049a23 <submitr+0x4b4>
 804997d:	80 bc 24 44 60 00 00 	cmpb   $0xd,0x6044(%esp)
 8049984:	0d
 8049985:	75 b5                	jne    804993c <submitr+0x3cd>
 8049987:	80 bc 24 45 60 00 00 	cmpb   $0xa,0x6045(%esp)
 804998e:	0a
 804998f:	75 ab                	jne    804993c <submitr+0x3cd>
 8049991:	80 bc 24 46 60 00 00 	cmpb   $0x0,0x6046(%esp)
 8049998:	00
 8049999:	75 a1                	jne    804993c <submitr+0x3cd>
 804999b:	b9 00 20 00 00       	mov    $0x2000,%ecx
 80499a0:	8d 94 24 44 60 00 00 	lea    0x6044(%esp),%edx
 80499a7:	8d 84 24 44 80 00 00 	lea    0x8044(%esp),%eax
 80499ae:	e8 75 fa ff ff       	call   8049428 <rio_readlineb>
 80499b3:	85 c0                	test   %eax,%eax
 80499b5:	7f 22                	jg     80499d9 <submitr+0x46a>
 80499b7:	be d8 a4 04 08       	mov    $0x804a4d8,%esi
 80499bc:	b9 0e 00 00 00       	mov    $0xe,%ecx
 80499c1:	8b bc 24 98 a0 00 00 	mov    0xa098(%esp),%edi
 80499c8:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 80499ca:	89 2c 24             	mov    %ebp,(%esp)
 80499cd:	e8 2e ef ff ff       	call   8048900 <close@plt>
 80499d2:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80499d7:	eb 4a                	jmp    8049a23 <submitr+0x4b4>
 80499d9:	8d 84 24 44 60 00 00 	lea    0x6044(%esp),%eax
 80499e0:	89 44 24 04          	mov    %eax,0x4(%esp)
 80499e4:	8b 84 24 98 a0 00 00 	mov    0xa098(%esp),%eax
 80499eb:	89 04 24             	mov    %eax,(%esp)
 80499ee:	e8 dd ed ff ff       	call   80487d0 <strcpy@plt>
 80499f3:	89 2c 24             	mov    %ebp,(%esp)
 80499f6:	e8 05 ef ff ff       	call   8048900 <close@plt>
 80499fb:	8b 8c 24 98 a0 00 00 	mov    0xa098(%esp),%ecx
 8049a02:	80 39 4f             	cmpb   $0x4f,(%ecx)
 8049a05:	75 10                	jne    8049a17 <submitr+0x4a8>
 8049a07:	80 79 01 4b          	cmpb   $0x4b,0x1(%ecx)
 8049a0b:	75 11                	jne    8049a1e <submitr+0x4af>
 8049a0d:	80 79 02 01          	cmpb   $0x1,0x2(%ecx)
 8049a11:	19 c0                	sbb    %eax,%eax
 8049a13:	f7 d0                	not    %eax
 8049a15:	eb 0c                	jmp    8049a23 <submitr+0x4b4>
 8049a17:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049a1c:	eb 05                	jmp    8049a23 <submitr+0x4b4>
 8049a1e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049a23:	81 c4 6c a0 00 00    	add    $0xa06c,%esp
 8049a29:	5b                   	pop    %ebx
 8049a2a:	5e                   	pop    %esi
 8049a2b:	5f                   	pop    %edi
 8049a2c:	5d                   	pop    %ebp
 8049a2d:	c3                   	ret
 8049a2e:	8d 84 24 44 40 00 00 	lea    0x4044(%esp),%eax
 8049a35:	89 44 24 1c          	mov    %eax,0x1c(%esp)
 8049a39:	8b 84 24 90 a0 00 00 	mov    0xa090(%esp),%eax
 8049a40:	89 44 24 18          	mov    %eax,0x18(%esp)
 8049a44:	8b 8c 24 8c a0 00 00 	mov    0xa08c(%esp),%ecx
 8049a4b:	89 4c 24 14          	mov    %ecx,0x14(%esp)
 8049a4f:	8b 84 24 88 a0 00 00 	mov    0xa088(%esp),%eax
 8049a56:	89 44 24 10          	mov    %eax,0x10(%esp)
 8049a5a:	c7 44 24 0c 10 a5 04 	movl   $0x804a510,0xc(%esp)
 8049a61:	08
 8049a62:	c7 44 24 08 00 20 00 	movl   $0x2000,0x8(%esp)
 8049a69:	00
 8049a6a:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049a71:	00
 8049a72:	8d bc 24 44 60 00 00 	lea    0x6044(%esp),%edi
 8049a79:	89 3c 24             	mov    %edi,(%esp)
 8049a7c:	e8 9f ee ff ff       	call   8048920 <__sprintf_chk@plt>
 8049a81:	b0 00                	mov    $0x0,%al
 8049a83:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049a88:	f2 ae                	repnz scas %es:(%edi),%al
 8049a8a:	f7 d1                	not    %ecx
 8049a8c:	89 cf                	mov    %ecx,%edi
 8049a8e:	4f                   	dec    %edi
 8049a8f:	0f 85 5f fd ff ff    	jne    80497f4 <submitr+0x285>
 8049a95:	e9 b5 fd ff ff       	jmp    804984f <submitr+0x2e0>

08049a9a <init_timeout>:
 8049a9a:	53                   	push   %ebx
 8049a9b:	83 ec 18             	sub    $0x18,%esp
 8049a9e:	8b 5c 24 20          	mov    0x20(%esp),%ebx
 8049aa2:	85 db                	test   %ebx,%ebx
 8049aa4:	74 27                	je     8049acd <init_timeout+0x33>
 8049aa6:	c7 44 24 04 3b 95 04 	movl   $0x804953b,0x4(%esp)
 8049aad:	08
 8049aae:	c7 04 24 0e 00 00 00 	movl   $0xe,(%esp)
 8049ab5:	e8 f6 ec ff ff       	call   80487b0 <signal@plt>
 8049aba:	89 d8                	mov    %ebx,%eax
 8049abc:	85 db                	test   %ebx,%ebx
 8049abe:	79 05                	jns    8049ac5 <init_timeout+0x2b>
 8049ac0:	b8 00 00 00 00       	mov    $0x0,%eax
 8049ac5:	89 04 24             	mov    %eax,(%esp)
 8049ac8:	e8 f3 ec ff ff       	call   80487c0 <alarm@plt>
 8049acd:	83 c4 18             	add    $0x18,%esp
 8049ad0:	5b                   	pop    %ebx
 8049ad1:	c3                   	ret

08049ad2 <init_driver>:
 8049ad2:	55                   	push   %ebp
 8049ad3:	57                   	push   %edi
 8049ad4:	56                   	push   %esi
 8049ad5:	53                   	push   %ebx
 8049ad6:	83 ec 3c             	sub    $0x3c,%esp
 8049ad9:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049ae0:	00
 8049ae1:	c7 04 24 0d 00 00 00 	movl   $0xd,(%esp)
 8049ae8:	e8 c3 ec ff ff       	call   80487b0 <signal@plt>
 8049aed:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049af4:	00
 8049af5:	c7 04 24 1d 00 00 00 	movl   $0x1d,(%esp)
 8049afc:	e8 af ec ff ff       	call   80487b0 <signal@plt>
 8049b01:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049b08:	00
 8049b09:	c7 04 24 1d 00 00 00 	movl   $0x1d,(%esp)
 8049b10:	e8 9b ec ff ff       	call   80487b0 <signal@plt>
 8049b15:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 8049b1c:	00
 8049b1d:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049b24:	00
 8049b25:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 8049b2c:	e8 7f ed ff ff       	call   80488b0 <socket@plt>
 8049b31:	89 c5                	mov    %eax,%ebp
 8049b33:	85 c0                	test   %eax,%eax
 8049b35:	79 1a                	jns    8049b51 <init_driver+0x7f>
 8049b37:	be 14 a3 04 08       	mov    $0x804a314,%esi
 8049b3c:	b9 26 00 00 00       	mov    $0x26,%ecx
 8049b41:	8b 7c 24 50          	mov    0x50(%esp),%edi
 8049b45:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 8049b47:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b4c:	e9 e2 00 00 00       	jmp    8049c33 <init_driver+0x161>
 8049b51:	c7 04 24 f8 a5 04 08 	movl   $0x804a5f8,(%esp)
 8049b58:	e8 73 ed ff ff       	call   80488d0 <gethostbyname@plt>
 8049b5d:	89 c2                	mov    %eax,%edx
 8049b5f:	85 c0                	test   %eax,%eax
 8049b61:	75 22                	jne    8049b85 <init_driver+0xb3>
 8049b63:	be 3c a3 04 08       	mov    $0x804a33c,%esi
 8049b68:	b9 2f 00 00 00       	mov    $0x2f,%ecx
 8049b6d:	8b 7c 24 50          	mov    0x50(%esp),%edi
 8049b71:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 8049b73:	89 2c 24             	mov    %ebp,(%esp)
 8049b76:	e8 85 ed ff ff       	call   8048900 <close@plt>
 8049b7b:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b80:	e9 ae 00 00 00       	jmp    8049c33 <init_driver+0x161>
 8049b85:	8d 5c 24 20          	lea    0x20(%esp),%ebx
 8049b89:	b9 10 00 00 00       	mov    $0x10,%ecx
 8049b8e:	b0 00                	mov    $0x0,%al
 8049b90:	89 df                	mov    %ebx,%edi
 8049b92:	f3 aa                	rep stos %al,%es:(%edi)
 8049b94:	66 c7 44 24 20 02 00 	movw   $0x2,0x20(%esp)
 8049b9b:	c7 44 24 0c 0c 00 00 	movl   $0xc,0xc(%esp)
 8049ba2:	00
 8049ba3:	8b 42 0c             	mov    0xc(%edx),%eax
 8049ba6:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049baa:	8b 42 10             	mov    0x10(%edx),%eax
 8049bad:	8b 00                	mov    (%eax),%eax
 8049baf:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049bb3:	8d 44 24 24          	lea    0x24(%esp),%eax
 8049bb7:	89 04 24             	mov    %eax,(%esp)
 8049bba:	e8 51 ec ff ff       	call   8048810 <__memmove_chk@plt>
 8049bbf:	66 c7 44 24 22 ff 8e 	movw   $0x8eff,0x22(%esp)
 8049bc6:	c7 44 24 08 10 00 00 	movl   $0x10,0x8(%esp)
 8049bcd:	00
 8049bce:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8049bd2:	89 2c 24             	mov    %ebp,(%esp)
 8049bd5:	e8 16 ed ff ff       	call   80488f0 <connect@plt>
 8049bda:	85 c0                	test   %eax,%eax
 8049bdc:	79 3b                	jns    8049c19 <init_driver+0x147>
 8049bde:	c7 44 24 10 f8 a5 04 	movl   $0x804a5f8,0x10(%esp)
 8049be5:	08
 8049be6:	c7 44 24 0c 5c a5 04 	movl   $0x804a55c,0xc(%esp)
 8049bed:	08
 8049bee:	c7 44 24 08 ff ff ff 	movl   $0xffffffff,0x8(%esp)
 8049bf5:	ff
 8049bf6:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049bfd:	00
 8049bfe:	8b 44 24 50          	mov    0x50(%esp),%eax
 8049c02:	89 04 24             	mov    %eax,(%esp)
 8049c05:	e8 16 ed ff ff       	call   8048920 <__sprintf_chk@plt>
 8049c0a:	89 2c 24             	mov    %ebp,(%esp)
 8049c0d:	e8 ee ec ff ff       	call   8048900 <close@plt>
 8049c12:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049c17:	eb 1a                	jmp    8049c33 <init_driver+0x161>
 8049c19:	89 2c 24             	mov    %ebp,(%esp)
 8049c1c:	e8 df ec ff ff       	call   8048900 <close@plt>
 8049c21:	8b 44 24 50          	mov    0x50(%esp),%eax
 8049c25:	66 c7 00 4f 4b       	movw   $0x4b4f,(%eax)
 8049c2a:	c6 40 02 00          	movb   $0x0,0x2(%eax)
 8049c2e:	b8 00 00 00 00       	mov    $0x0,%eax
 8049c33:	83 c4 3c             	add    $0x3c,%esp
 8049c36:	5b                   	pop    %ebx
 8049c37:	5e                   	pop    %esi
 8049c38:	5f                   	pop    %edi
 8049c39:	5d                   	pop    %ebp
 8049c3a:	c3                   	ret

08049c3b <no_connection>:
 8049c3b:	83 ec 1c             	sub    $0x1c,%esp
 8049c3e:	c7 04 24 84 a5 04 08 	movl   $0x804a584,(%esp)
 8049c45:	e8 b6 eb ff ff       	call   8048800 <puts@plt>
 8049c4a:	8b 44 24 20          	mov    0x20(%esp),%eax
 8049c4e:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049c52:	c7 44 24 04 07 a6 04 	movl   $0x804a607,0x4(%esp)
 8049c59:	08
 8049c5a:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8049c61:	e8 3a ec ff ff       	call   80488a0 <__printf_chk@plt>
 8049c66:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8049c6d:	e8 ce eb ff ff       	call   8048840 <exit@plt>

08049c72 <phase_init>:
 8049c72:	57                   	push   %edi
 8049c73:	56                   	push   %esi
 8049c74:	53                   	push   %ebx
 8049c75:	83 ec 20             	sub    $0x20,%esp
 8049c78:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 8049c7f:	00
 8049c80:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049c87:	00
 8049c88:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 8049c8f:	e8 1c ec ff ff       	call   80488b0 <socket@plt>
 8049c94:	89 c3                	mov    %eax,%ebx
 8049c96:	85 c0                	test   %eax,%eax
 8049c98:	79 0c                	jns    8049ca6 <phase_init+0x34>
 8049c9a:	c7 04 24 14 a3 04 08 	movl   $0x804a314,(%esp)
 8049ca1:	e8 95 ff ff ff       	call   8049c3b <no_connection>
 8049ca6:	c7 04 24 f8 a5 04 08 	movl   $0x804a5f8,(%esp)
 8049cad:	e8 1e ec ff ff       	call   80488d0 <gethostbyname@plt>
 8049cb2:	89 c2                	mov    %eax,%edx
 8049cb4:	85 c0                	test   %eax,%eax
 8049cb6:	75 0c                	jne    8049cc4 <phase_init+0x52>
 8049cb8:	c7 04 24 3c a3 04 08 	movl   $0x804a33c,(%esp)
 8049cbf:	e8 77 ff ff ff       	call   8049c3b <no_connection>
 8049cc4:	8d 74 24 10          	lea    0x10(%esp),%esi
 8049cc8:	b9 10 00 00 00       	mov    $0x10,%ecx
 8049ccd:	b0 00                	mov    $0x0,%al
 8049ccf:	89 f7                	mov    %esi,%edi
 8049cd1:	f3 aa                	rep stos %al,%es:(%edi)
 8049cd3:	66 c7 44 24 10 02 00 	movw   $0x2,0x10(%esp)
 8049cda:	c7 44 24 0c 0c 00 00 	movl   $0xc,0xc(%esp)
 8049ce1:	00
 8049ce2:	8b 42 0c             	mov    0xc(%edx),%eax
 8049ce5:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049ce9:	8b 42 10             	mov    0x10(%edx),%eax
 8049cec:	8b 00                	mov    (%eax),%eax
 8049cee:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049cf2:	8d 44 24 14          	lea    0x14(%esp),%eax
 8049cf6:	89 04 24             	mov    %eax,(%esp)
 8049cf9:	e8 12 eb ff ff       	call   8048810 <__memmove_chk@plt>
 8049cfe:	66 c7 44 24 12 ff 8e 	movw   $0x8eff,0x12(%esp)
 8049d05:	c7 44 24 08 10 00 00 	movl   $0x10,0x8(%esp)
 8049d0c:	00
 8049d0d:	89 74 24 04          	mov    %esi,0x4(%esp)
 8049d11:	89 1c 24             	mov    %ebx,(%esp)
 8049d14:	e8 d7 eb ff ff       	call   80488f0 <connect@plt>
 8049d19:	85 c0                	test   %eax,%eax
 8049d1b:	79 0c                	jns    8049d29 <phase_init+0xb7>
 8049d1d:	c7 04 24 bc a5 04 08 	movl   $0x804a5bc,(%esp)
 8049d24:	e8 12 ff ff ff       	call   8049c3b <no_connection>
 8049d29:	89 1c 24             	mov    %ebx,(%esp)
 8049d2c:	e8 cf eb ff ff       	call   8048900 <close@plt>
 8049d31:	b8 00 00 00 00       	mov    $0x0,%eax
 8049d36:	83 c4 20             	add    $0x20,%esp
 8049d39:	5b                   	pop    %ebx
 8049d3a:	5e                   	pop    %esi
 8049d3b:	5f                   	pop    %edi
 8049d3c:	c3                   	ret

08049d3d <driver_post>:
 8049d3d:	53                   	push   %ebx
 8049d3e:	83 ec 28             	sub    $0x28,%esp
 8049d41:	8b 44 24 30          	mov    0x30(%esp),%eax
 8049d45:	8b 54 24 34          	mov    0x34(%esp),%edx
 8049d49:	8b 5c 24 3c          	mov    0x3c(%esp),%ebx
 8049d4d:	83 7c 24 38 00       	cmpl   $0x0,0x38(%esp)
 8049d52:	74 28                	je     8049d7c <driver_post+0x3f>
 8049d54:	89 54 24 08          	mov    %edx,0x8(%esp)
 8049d58:	c7 44 24 04 20 a6 04 	movl   $0x804a620,0x4(%esp)
 8049d5f:	08
 8049d60:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8049d67:	e8 34 eb ff ff       	call   80488a0 <__printf_chk@plt>
 8049d6c:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049d71:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049d75:	b8 00 00 00 00       	mov    $0x0,%eax
 8049d7a:	eb 49                	jmp    8049dc5 <driver_post+0x88>
 8049d7c:	85 c0                	test   %eax,%eax
 8049d7e:	74 37                	je     8049db7 <driver_post+0x7a>
 8049d80:	80 38 00             	cmpb   $0x0,(%eax)
 8049d83:	74 32                	je     8049db7 <driver_post+0x7a>
 8049d85:	89 5c 24 18          	mov    %ebx,0x18(%esp)
 8049d89:	89 54 24 14          	mov    %edx,0x14(%esp)
 8049d8d:	c7 44 24 10 37 a6 04 	movl   $0x804a637,0x10(%esp)
 8049d94:	08
 8049d95:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8049d99:	c7 44 24 08 3f a6 04 	movl   $0x804a63f,0x8(%esp)
 8049da0:	08
 8049da1:	c7 44 24 04 8e ff 00 	movl   $0xff8e,0x4(%esp)
 8049da8:	00
 8049da9:	c7 04 24 f8 a5 04 08 	movl   $0x804a5f8,(%esp)
 8049db0:	e8 ba f7 ff ff       	call   804956f <submitr>
 8049db5:	eb 0e                	jmp    8049dc5 <driver_post+0x88>
 8049db7:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049dbc:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049dc0:	b8 00 00 00 00       	mov    $0x0,%eax
 8049dc5:	83 c4 28             	add    $0x28,%esp
 8049dc8:	5b                   	pop    %ebx
 8049dc9:	c3                   	ret
 8049dca:	90                   	nop
 8049dcb:	90                   	nop
 8049dcc:	90                   	nop
 8049dcd:	90                   	nop
 8049dce:	90                   	nop
 8049dcf:	90                   	nop

08049dd0 <__libc_csu_init>:
 8049dd0:	55                   	push   %ebp
 8049dd1:	89 e5                	mov    %esp,%ebp
 8049dd3:	57                   	push   %edi
 8049dd4:	56                   	push   %esi
 8049dd5:	53                   	push   %ebx
 8049dd6:	e8 5a 00 00 00       	call   8049e35 <__i686.get_pc_thunk.bx>
 8049ddb:	81 c3 19 22 00 00    	add    $0x2219,%ebx
 8049de1:	83 ec 1c             	sub    $0x1c,%esp
 8049de4:	e8 77 e9 ff ff       	call   8048760 <_init>
 8049de9:	8d bb 18 ff ff ff    	lea    -0xe8(%ebx),%edi
 8049def:	8d 83 18 ff ff ff    	lea    -0xe8(%ebx),%eax
 8049df5:	29 c7                	sub    %eax,%edi
 8049df7:	c1 ff 02             	sar    $0x2,%edi
 8049dfa:	85 ff                	test   %edi,%edi
 8049dfc:	74 24                	je     8049e22 <__libc_csu_init+0x52>
 8049dfe:	31 f6                	xor    %esi,%esi
 8049e00:	8b 45 10             	mov    0x10(%ebp),%eax
 8049e03:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049e07:	8b 45 0c             	mov    0xc(%ebp),%eax
 8049e0a:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049e0e:	8b 45 08             	mov    0x8(%ebp),%eax
 8049e11:	89 04 24             	mov    %eax,(%esp)
 8049e14:	ff 94 b3 18 ff ff ff 	call   *-0xe8(%ebx,%esi,4)
 8049e1b:	83 c6 01             	add    $0x1,%esi
 8049e1e:	39 fe                	cmp    %edi,%esi
 8049e20:	72 de                	jb     8049e00 <__libc_csu_init+0x30>
 8049e22:	83 c4 1c             	add    $0x1c,%esp
 8049e25:	5b                   	pop    %ebx
 8049e26:	5e                   	pop    %esi
 8049e27:	5f                   	pop    %edi
 8049e28:	5d                   	pop    %ebp
 8049e29:	c3                   	ret
 8049e2a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

08049e30 <__libc_csu_fini>:
 8049e30:	55                   	push   %ebp
 8049e31:	89 e5                	mov    %esp,%ebp
 8049e33:	5d                   	pop    %ebp
 8049e34:	c3                   	ret

08049e35 <__i686.get_pc_thunk.bx>:
 8049e35:	8b 1c 24             	mov    (%esp),%ebx
 8049e38:	c3                   	ret
 8049e39:	90                   	nop
 8049e3a:	90                   	nop
 8049e3b:	90                   	nop
 8049e3c:	90                   	nop
 8049e3d:	90                   	nop
 8049e3e:	90                   	nop
 8049e3f:	90                   	nop
 8049e40:	55                   	push   %ebp
 8049e41:	89 e5                	mov    %esp,%ebp
 8049e43:	53                   	push   %ebx
 8049e44:	83 ec 04             	sub    $0x4,%esp
 8049e47:	a1 0c bf 04 08       	mov    0x804bf0c,%eax
 8049e4c:	83 f8 ff             	cmp    $0xffffffff,%eax
 8049e4f:	74 1b                	je     8049e6c <__i686.get_pc_thunk.bx+0x37>
 8049e51:	bb 0c bf 04 08       	mov    $0x804bf0c,%ebx
 8049e56:	8d 76 00             	lea    0x0(%esi),%esi
 8049e59:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
 8049e60:	ff d0                	call   *%eax
 8049e62:	83 eb 04             	sub    $0x4,%ebx
 8049e65:	8b 03                	mov    (%ebx),%eax
 8049e67:	83 f8 ff             	cmp    $0xffffffff,%eax
 8049e6a:	75 f4                	jne    8049e60 <__i686.get_pc_thunk.bx+0x2b>
 8049e6c:	83 c4 04             	add    $0x4,%esp
 8049e6f:	5b                   	pop    %ebx
 8049e70:	5d                   	pop    %ebp
 8049e71:	c3                   	ret
 8049e72:	90                   	nop
 8049e73:	90                   	nop

Disassembly of section .fini:

08049e74 <_fini>:
 8049e74:	55                   	push   %ebp
 8049e75:	89 e5                	mov    %esp,%ebp
 8049e77:	53                   	push   %ebx
 8049e78:	83 ec 04             	sub    $0x4,%esp
 8049e7b:	e8 00 00 00 00       	call   8049e80 <_fini+0xc>
 8049e80:	5b                   	pop    %ebx
 8049e81:	81 c3 74 21 00 00    	add    $0x2174,%ebx
 8049e87:	e8 f4 ea ff ff       	call   8048980 <_start+0x50>
 8049e8c:	59                   	pop    %ecx
 8049e8d:	5b                   	pop    %ebx
 8049e8e:	c9                   	leave
 8049e8f:	c3                   	ret
