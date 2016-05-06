
		���\�t���u���b�N���x���\��XML�ɂ���

1. �͂��߂�
===========

���\�t���u���b�N���x���\��XML�̐�������@�\�ɂ��ďq�ׂ܂��B

�{�@�\�́A�ȉ��̎O�̃v���O�����A���W���[������Ȃ�܂��B

(1) blxml-perf.sh

    �u���b�N���x���\��XML�̃R�[�h�f�Ђ̐��\���Z�o���A���\�t���u���b�N��
    �x���\��XML���o�͂���ׂ̈�A�̏��������s����V�F���X�N���v�g�ł��B

(2) blxml2code

    �u���b�N���x���\��XML�̃R�[�h�f�Ђ���A�R���p�C���\��C�R�[�h��
    ������v���O�����ł��B���������R�[�h��LLVM�ŃR���p�C�����A��q����
    LLVM��Pass(llvm-BLXMLPerf.so)��ʂ����ŁA���\���Z�o����܂��B

(3) llvm-BLXMLPerf.so

    �u���b�N���x���\��XML�̃u���b�N���̃R�[�h(task,update,init)�P�ʂ̐�
    �\���v�����A���\�t���u���b�N���x���\��XML���o�͂��邽�߂ɗ��p����
    LLVM��Pass�ł��B


2. �@�\����
===========

2.1. blxml-perf.sh
==================

�u���b�N���x���\��XML�̃R�[�h�f�Ђ̐��\���Z�o���A���\�t���u���b�N���x��
�\��XML���o�͂���ׂ̈�A�̏��������s����V�F���X�N���v�g�ł��B

2.1.1. ���s
===========

  blxml-perf.sh [-v] [-o output] [-shim=SHIM] [-shim-schema=SCHEMA] \
        [-C clang-option] [-0 pass-option] [-S pass-module] INPUT-XML

�R�}���h�I�v�V�����͈ȉ��̒ʂ�ł��B

  -v                  : (optional) verbose option
  -o output           : (optional) Output BLXML
  -shim=SHIM          : (optional) SHIM File included `CommonInstructionSet'
  -shim-schema=SCHEMA : (optional) SHIM Schema for validation
  -C clang-option     : (optional) add CLANG options as `-O', `-I', etc
  -O pass-option      : (optional) add LLVM pass options, see below
  -S pass-module      : (optional) use LLVM Pass Module

-O�I�v�V�����́A�ȉ��̎l��LLVM��Pass(llvm-BLXMLPerf.so)�̃I�v�V������
���A�C�ӂ�opt�R�}���h�̃I�v�V�������w��ł��܂��B

  -O -MasterComponent=name      : Name of SHIM MasterComponent
  -O -CommonInstructionSet=name : Name of SHIM CommonInstructionSet
  -O -no-ret                    : Not count LLVM ReturnInstruction
  -O -no-br                     : Not count LLVM BranchInstruction
  -O -out-dot=basename          : basename of output GraphViz DOT file

�Ⴆ��pid�ł͈ȉ��̂悤�Ɏ��s���܂��B

  ./blxml-perf.sh -v \
      -o models/pid/test_blxml.xml \
      -shim=SHIM.xml \
      -C -Imodels/pid/pid_controller1_ert_rtw/ \
      -C -O \
      models/pid/yy.xml

�@(1) model/pid/yy.xml ����model/pid/test_blxml.xml�𐶐����܂�
  (2) SHIM�Ƃ��āASHIM.xml���g�p���܂�(schema�ɂ��validation�͍s���܂���)
  (3) -C��clang�ւ̃I�v�V�����ŁAblxml2code�ɂ���Đ������ꂽ�R�[�h���g
      �p���� rtwtypes.h �̃C���N���[�h�p�X(-I)�ƁA�I�v�e�B�}�C�Y(-O)��
      �w�肵�܂�

�� clang��-O�I�v�V����(�I�v�e�B�}�C�Y)���s���ꍇ�Ƃ����łȂ��ꍇ�ł́A
   ���[�v�̍\���ɍ��ق��o�āA�Œ�񐔂��邢�͍ő�񐔂��킩��Ȃ����[�v
   �ɂȂ�P�[�X������܂��B���̏ꍇ�A���[�v�̃C�e���[�V�����̏����ʂ͌v
   �Z����܂���B(-C -O�̂���/�Ȃ�)

�� opt��-mem2reg���w�肵�������A���[�v�̉񐔂�K�؂Ɍ��o�ł���悤�ł�
   (�I�v�V������ -O -mem2reg)

���ϐ��Ƃ��āA�ȉ��̂��̂��w�肷�鎖���ł��܂��B

  BLXML2CODE     -- blxml2code�̃v���O�������B�f�t�H���g�ł�blxm2code
  CLANG          -- LLVM CLANG�̃v���O�������B�f�t�H���g�ł�clang
  LLVM_OPT       -- LLVM��opt�̃v���O�������B�f�t�H���g�ł�opt
  LLVM_BLXMLPERF -- ���\�Z�o�pLLVM��Pass�B�t�H���g�� ./llvm-BLXMLPerf.so

�� BLXML2CODE,CLANG,LLVM_OPT��ύX���Ȃ��ꍇ�A�e�v���O���������s�ł���
   �悤�� PATH ���ϐ���ݒ肵�Ă��������B���ɁA�J�����g�f�B���N�g����
   blxml2code�����s����K�v������ꍇ�APATH��"."���܂܂�˂΂Ȃ�܂���B


2.1.2. ������e
===============

���̃v���O�����́A�ȉ��̂悤�ɓ��삵�܂�

  (1) blxml2code�ɂ�萫�\����p�R�[�h�𐶐�����
  (2) clang�ŏ�L�R�[�h��LLVM�̃A�Z���u���ɃR���p�C������
  (3) llvm-BLXMLPerf��p���A�R���p�C�����ꂽ�R�[�h�̐��\�l(�T�C�N����)
      ���Z�o���A���̐��\�l�𐫔\�t���u���b�N���x���\��XML�ɏo�͂���


2.2. blxml2code
===============

�����̃v���O������blxml-perf.sh������s����܂�

�u���b�N���x���\��XML�̃R�[�h�f�Ђ���A�R���p�C���\��C�R�[�h�𐶐���
��v���O�����ł��B

2.2.1. ���s
===========

  blxml2code [-o output] [input]

�R�}���h�I�v�V�����͈ȉ��̒ʂ�ł��B

  -o output : (optional) output C code

-o���w�肳��Ȃ��ꍇ�A�W���o�͂փ\�[�X�R�[�h���o�͂��܂��Binput���w�肳
��Ȃ��ꍇ�A�W�����͂���XML��ǂݍ��݂܂��B

�Ⴆ��pid�ł͈ȉ��̂悤�Ɏ��s���܂��B

  ./blxml2code -o xxx.c models/pid/yy.xml

�������ꂽ�R�[�h���R���p�C������ׂɂ� rtwtypes.h ���K�v�ł��B�R���p�C
���̍ۂɂ́A���̃t�@�C�������݂���f�B���N�g����clang��-I�I�v�V�����Ŏw
�肵�Ă��������B

clan�ŃR���p�C������ꍇ�́A�Ⴆ�Ύ��̂悤�ɂ��܂��B

  clang -S -O -I<path fof rtwtype.h> -emit-llvm -o xxx.ll xxx.c


2.2.2. �R�[�h�ɂ���
=====================

�{�v���O��������������R�[�h�́A���\����̂��߂̃R���p�C���\�ȃR�[�h
�𐶐����鎖���ړI�ł���A���̃��f���̋@�\������������̂ł͂���܂���B

�܂��A�e�u���b�N�Ŏg�p������͑��ϐ��͊֐��p�����^�Ƃ��Ēl�n������A
�o�͕ϐ��̓|�C���^�Ƃ��Ĉ�����悤�ɂ��܂��B��ԕϐ���p�����^�́A
�t�@�C���X�R�[�v�̕ϐ��Ƃ��Ē�`����܂��B


2.3. llvm-BLXMLPerf.so
======================

�����̏�����blxml-perf.sh������s����܂�

�u���b�N���x���\��XML�̃u���b�N���̃R�[�h(task,update,init)�P�ʂ̐��\��
�v�����A���\�t���u���b�N���x���\��XML���o�͂��邽�߂ɗ��p����LLVM��
Pass�ł��B

2.3.1. ���s
===========

�{Pass�͈ȉ��̂悤�Ɏ��s���܂��B

  opt -load=<path for llvm-BLXMLPerf.so> -S -blxml-perf \
    [-shim=SHIM] [-shim-schema=SCHEMA] \
    [-MasterComponent=name] [-CommonInstructionSet=name] \
    [-no-ret] [-no-br] \
    [-in-xml=INPUT.XML] [-out-xml=OUTPUT.XML] \
    -o dummy_output.ll input.ll

llvm-BLXMLPerf.so�̃I�v�V�����͈ȉ��̒ʂ�ł��B

  -shim=SHIM                 : (optional) SHIM File
  -shim-schema=SCHEMA        : (optional) SHIM Schema for validation
  -MasterComponent=name      : (optional) Name of MasterComponent
  -CommonInstructionSet=name : (optional) Name of CommonInstructionSet
  -no-ret                    : (optional) Not count LLVM ReturnInstruction
  -no-br                     : (optional) Not count LLVM BranchInstruction
  -in-xml=INPUT.XML          : (required) input BLXML 
  -out-xml=OUTPUT.XML        : (optional) output BLXML
  -out-dot=basename          : (optional) basename of output GraphViz DOT file

-shim=-no �Ƃ����ꍇ�ASHIM����͂����A�T�C�N����1�Ƃ��Đ��\���Z�o���܂��B
���̏ꍇ�A���s���A���ߖ��ɃG���[���o�͂��܂��B

-shim-schema���w�肵�Ȃ��ꍇ�AXML�̃`�F�b�N(validation)�͍s���܂���B

���߂̃T�C�N�������擾����ASHIM��CommonInstructionSet����肷�邽�߁A
MasterComponent��CommonInstructionSet�̑����̖��O���w�肷�鎖���ł��܂��B
�������w�肵�Ȃ��ꍇ�A�ŏ��Ɍ����� CommonInstructionSet���g�p���܂��B

-no-ret�́A���\�Z�o�̍ہARET���߂̃T�C�N���𖳎����܂��B����̓u���b�N
�̃R�[�h�̒f�Ђ́Ablxml2code�ł͈�̊֐��Ƃ��Đ�������̂�RET�̃I�[�o
�w�b�h�𖳎�����ꍇ�Ɏg�p���܂��B

-no-br�́A��{�u���b�N�Ԃ̕��򖽗߂̃T�C�N���𖳎����܂��B(���ꂪ�L����
���ʂɌq����P�[�X�͂��܂�Ȃ��Ǝv���܂����A�ꉞ����)

-in-xml�ɂ����͂̃u���b�N���x���\��XML�́Ablxml2code�ŃR�[�h�����Ɏg
�p����XML�t�@�C���łȂ���΂Ȃ�܂���B

-out-xml�͏ȗ��\�ŁA�ȗ������ꍇ�A���\�t���u���b�N���x���\��XML��W��
�o�͂ɏo�͂��܂��B

-out-dot�͏ȗ��\�ł��B���̃I�v�V�������w�肵���ꍇ�A
basename-<�ԍ�>.dot �Ƃ���GraphViz�̃t�@�C�������[�v����ъ֐����ɏ���
�������܂��B


2.3.2. dot�t�@�C��
==================

dot�t�@�C����GraphViz�̃t�@�C���ŁA�����ʂ��v�Z�����ۂ̌o�H�T�����ʂł��B
�֐��P�ʂ̏����Ƃ��Ă͍œ����[�v����o�͂��A�Ō�ɃR�[�h�S��(�֐�)�̃O
���t�ɂȂ�܂��B

�m�[�h�͊�{�u���b�N�܂��͂܂Ƃ߂�ꂽ�Œ���郋�[�v�ł��B

�E�Ԙg(red)���h��Ԃ���Ă���m�[�h(plum)�́A�Œ���郋�[�v�����
  �ɂ܂Ƃ߂�����
�E�g(blue)�̃m�[�h�́A�ő�񐔂��킩���Ă��郋�[�v�̃w�b�h(��{�u���b�N)
�E����ȊO�̃m�[�h�͒ʏ�̊�{�u���b�N
�Ebox�̃m�[�h�́A���[�v�̃w�b�h�ւ�backedge���������߂̃_�~�[�m�[�h
�E�����̐����͏ォ�珇�ɁA���̃m�[�h��best/typical/worst�̏����T�C�N��
�E�Ō��[]���̐����́A�I�[�܂ł̕��Ϗ������Ԃł�(successor�̊e��������
  �Ɠ��m������ɂ���ĕ��ω�������������)

�G�b�W��successor�ɂȂ�܂��B

�E��(green)�͍ŒZ�o�H
�E��(blue)�͍Œ��o�H�B�Œ��o�H���ŒZ�o�H�Əd�Ȃ�ꍇ�́A�ŒZ�o�H�̕\��
  ���D��
�E��(red)�̔j���̓��[�v�̃o�b�N�G�b�W
�E���̔j���̓_�~�[�m�[�h�ւ̐ڑ�������
�E�����̓w�b�h�̃m�[�h�̏������Ԃ��o�H�T���̂��߂̋���(distance)�ŁA��
  ���珇��best/typical/worst�ƂȂ�


2.3.2. �����T�v
===============

�{Pass�͂��̂悤�ɂȂ��Ă��܂�

  (1) FunctionPass���p�����Ă���A�֐��P�ʂɏ������s��
  (2) ���O�� LoopInfo Pass�� ScalarEvolution Pass�����s����
  (3) ����������SHIM�ƃu���b�N���x���\��XML��ǂݍ���
  (4) �I�����ɐ��\�t���u���b�N���x���\��XML���o�͂���

�֐��P�ʂ̏����͈ȉ��̂悤�ɂȂ��Ă��܂��B

  (1) ��{�u���b�N�̃|�C���^���L�[�Ƃ����A�z�z����쐬(�t�����̕ێ��̂���)
  (2) ��{�u���b�N�̃T�C�N����(best/typical/worst)���Z�o���A�A�z�z���
      �ۑ�
  (3) LoopInfo��ScalarEvolution�����Ƀ��[�v�̏��������{
  (4) ��{�u���b�N��successor����ъ�{�u���b�N���܂Ƃ߂����[�v�̏��
      (LoopInfo�ɂ��A�z�z��)����A�L���O���t���쐬����(boost�̃O���t
      ���C�u�������g�p����)
  (5) �ŒZ�o�H/best�A�Œ��o�H/worst�A����m��50%/typical�ɂ��o�H�T��
      �����{���A�֐��̃T�C�N����(best/typical/worst)���Z�o���A�֐��̏�
      ��Ƃ��ĕۑ�

���[�v�̏����͂��̂悤�ɍs���܂�

  (1) LoopInfo�œ����[�v���珈������悤�ċA��������
  (2) ScalarEvolution�̌��ʂ���Œ���郋�[�v�Ȃ�A���[�v�Ƃ��Ċ�{�u
      ���b�N����̃O���t�Ƃ��āA���[�v���̊�{�u���b�N�̃T�C�N������
      �ŒZ�o�H/best, ����m��50%/typical�A�Œ��o�H/worst�ʂɎZ�o�A
      best/worst/typical�Ƃ����[�v�񐔕����Z����B
  (3) �ő�񐔂��킩�郋�[�v(�r���Ŕ����o�����Ƃ�����)�Ȃ�A���[�v�Ƃ�
      �Ċ�{�u���b�N����̃O���t�Ƃ��āA���[�v���̊�{�u���b�N�̃T�C
      �N������best/typical/worst�ʂɉ��Z�Aworst�������[�v�񐔕����Z����B
      best/typical�͈�񂾂������̂Ƃ���B
  (4) ��L�̃��[�v�̊�{�u���b�N�̏���LoopInfo�̃|�C���^���L�[�Ƃ���
      �A�z�z��ɕۑ�����
  (5) ��L������ł��Ȃ����[�v�́A��{�u���b�N�����[�v�Ƃ��Ă܂Ƃ߂Ȃ�
      (�܂�A��񂾂������̂Ƃ��Ď�舵�����ƂɂȂ�)


���[�v���̊�{�u���b�N���֐��S�̂ɂ��Ă��O���t�T���͂��̂悤�ɍs��
�܂��B

  (1) best�l���G�b�W�ɋ����Ƃ��Đݒ肵dijkstra�̃A���S���Y���ōŒZ�o�H
      �T�����s��(boost�̃A���S���Y�����g�p)
  (2) worst�l�̕������G�b�W�ɋ����Ƃ��Đݒ肵�Abellman-ford�̃A���S���Y
      ���ōŒZ�o�H�T�����s��(���ʂƂ��čŒ��o�H�ɂȂ�)�B(boost�̃A���S
      ���Y�����g�p)
  (3) ����m��50%(���m������)��typical�̒T���́A�ċA�I��depth first�ōs
      ���B���[�v�����o(GRAY)�����ꍇ�͒T����ł�����(�܂肻�̕���͓�
      ����Ȃ�)�B���B�ς݃m�[�h(BLACK)�ł���΁A���ʃm�[�h�̌v�Z�ς݂�
      �T�C�N�������Z���čs���B�Ō�ɕ��򐔂Ŋ����ăT�C�N�����Ƃ���B

�ȏ�
