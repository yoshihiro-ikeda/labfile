
		    Simulink���f����XML�Ή��̃���

1. �͂��߂�
===========

�{�����́AXML�o�͌��ʊm�F�p�ɒ񋟂��錻�݂̃v���O�����ł��B

�{�t�@�C���ȉ��̋@�\��L���܂�

�ESimulink���璊�o���ꂽXML��ǂ݁ARTW�̃R�[�h�𒊏o���Ė��ߍ���XML�t�@
  �C��(BLXML)���o�͂���v���O����
�EBLXML��RTW�̃R�[�h�̒f�Ђɂ��āA���\���v�Z���AXML�ɖ��ߍ��ރv���O����

�ȉ��͊e�t�@�C���̊T�v�ł��B

  Simulink_XSD/SimulinkModel.m4        -- XML�X�L�[�}�̃e���v���[�g
  Simulink_XSD/SimulinkXSD.xslx        -- �X�L�[�}�̐���(Excel�t�@�C��)

  Simulink_XSD/xsd_driver.cxx          -- XML�X�L�[�}�̃e�X�g�R�[�h

  Simulink_XSD/SimulinkRTW.cxx         -- RTW�̃R�[�h�������W���[��
  Simulink_XSD/SimulinkRTW.h           -- ���W���[���̃w�b�_�t�@�C��
  Simulink_XSD/rtw_test.cxx            -- RTW�̃R�[�h�����̃e�X�g�R�[�h

  Simulink_XSD/SimulinkXML.cxx         -- RTW�𖄂ߍ���XML�̏����x���R�[�h
  Simulink_XSD/SimulinkXML.h           -- ��L�p�w�b�_
  Simulink_XSD/xml_test.cxx            -- ��L�e�X�g�R�[�h

  Simulink_XSD/blxml2code.cxx          -- �v���R�[�h�𐶐�����v���O����

  Simulink_XSD/shim-schema.xsd         -- 4/14����SHIM�X�L�[�}

  Simulink_XSD/SHIM.xml                -- v850�v���ł�SHIM�T���v��

  Simulink_XSD/llvm-BLXMLPerf.cxx      -- BLXML�p��LLVM��Pass�̃\�[�X
  Simulink_XSD/llvm-BLXMLPerf.h        -- ��L�p�w�b�_
  Simulink_XSD/blxml_llvm.cxx          -- ��L��BLXML�A�N�Z�X�p�R�[�h
  Simulink_XSD/blxml_llvm.h            -- ��L�p�w�b�_
  Simulink_XSD/shim_llvm.cxx           -- ��L��SHIM�A�N�Z�X�p�R�[�h
  Simulink_XSD/shim_llvm.h             -- ��L�p�w�b�_
  Simulink_XSD/boost_llvm.cxx          -- �O�o������boost�̃\�[�X

  Simulink_XSD/blxml-perf.sh           -- BLXML�𐫔\�t��BLXML�ɂ���X�N���v�g

  Simulink_XSD/models/pid/xx.xml       -- pid_controller1.xml�̏�������
  Simulink_XSD/models/cell/xx.xml      -- vipcellcounting_win.xml�̏�������
  Simulink_XSD/models/test1/xx.xml     -- testsys.xml�̏�������
  Simulink_XSD/models/testmux/xx.xml   -- testmux3.xml�̏�������

  Simulink_XSD/Makefile                -- Makefile


2. �R���p�C����
=================

�R���p�C���� Fedora 20(x64), CentOS6.5(x64)��Solaris11.1(x64)�Ŋm�F����
���܂��B


2.1. �K�v�ȃp�b�P�[�W
=====================

2.1.1. CodeSynthesis XSD
========================

C++�̃f�[�^�o�C���f�B���O�̃R�[�h�����̂��߁ACodeSynthesis��XSD���K�v��
���BLinux�ł̓p�b�P�[�W������Ă���̂ŁA�������Ă��������B
(CentOS�ł�RedHat��EPEL���|�W�g�����瓱���\�ł�)

�܂��A�e�R�}���h�����s�ł���悤�A�K�v�ł���� PATH ���ϐ��̐ݒ���s��
�Ă��������B

2.1.2  Xerces-C++
=================

XSD��Apache Project��Xerces-C++���K�v�ł��BLinux�ł̓p�b�P�[�W�������
����̂œ������Ă��������B

�܂��Apkg-config�ɂď�񂪎擾�ł���悤�A�K�v�ł���� PKG_CONFIG_PATH
���ϐ����̐ݒ�����{���Ă��������B

2.1.3. boost���C�u����
======================

GNU C++��regex�͖������̂��߁A���K�\���̏����ɂ�boost-regex���C�u������
�g�p���Ă��܂��B�܂��A������u����boost���C�u������algorithm���g�p����
���܂��BLinux�ł̓p�b�P�[�W������Ă���̂�boost���C�u�����𓱓����Ă�
�������B

2.1.4. graphviz
===============

�u���b�N�̐ڑ������O���t�\�����邽�߂ɂ�graphviz���K�v�ł��BLinux�ł�
�p�b�P�[�W������Ă���̂œ������Ă��������B

2.1.5. llvm3.4
==============

LLVM 3.4�̊J�������K�v�ł��BLinux�ł̓p�b�P�[�W������Ă���̂ŁA����
���Ă��������B(CentOS�ł�RedHat��EPEL���|�W�g�����瓱���\�ł�)

�܂��A�e�R�}���h�����s�ł���悤�A�K�v�ł���� PATH ���ϐ��̐ݒ���s��
�Ă��������B


3. �K�v�ȃe�X�g�f�[�^
=====================

11/29���񋟂�models.zip�� models �ȉ��ɓW�J���Ă��������B
�g�p����̂�RTW-EC��C�\�[�X�A�w�b�_�A�p�����^�����l�̃t�@�C���ł��B
XML�́A���Y�f�B���N�g����xx.xml���g�p���܂��B

SHIM�̃X�L�[�} shim-schema.xsd ���K�v�ł��B(�������Ă��܂�)


3.1. XML�t�@�C���ɂ���
========================

�f�[�^�o�C���f�B���O���g�p����ɂ�����A�l�[���X�y�[�X�̑Ή����K�v�ɂ�
��܂��B

�擪��blocks�͈ȉ��̂悤�ɕύX����K�v������܂��B

  <blocks>
  ��
  <sm:blocks
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://example.com/SimulinkModel SimulinkModel.xsd"
    xmlns:sm="http://example.com/SimulinkModel"
    name="pid_controller1">        // ����� pid �p�̖��O�ł�

�����XML�X�L�[�}�̖��O��Ԃ̓v���t�B�N�X xsi �����邱�ƂɂȂ�܂��B
�܂�blocks�̓O���[�o���^�O�Ȃ̂ŁA���O���sm�ň����܂��B����ȊO��
blocks�ɂ��v���t�B�N�X�Ƃ��� sm ������K�v������܂��B

  <blocks> �� <sm:blocks>

blocks�̏I���^�O���ȉ��̂悤�� sm ��t���܂��B

  </blocks> �� </sm:blocks>

�ύX�󋵂ɂ��ẮAmodels.zip��W�J��ɗႦ�Έȉ����r���Ă݂Ă�����
���B

  models/pid/pid_controller1.xml
  models/pid/xx.xml


���O��Ԃ̎��ʎq�Ƃ��� "http://example.com/SimulinkModel" ���g�p���Ă�
�܂��B�����ύX����ꍇ�AMakefile��SIM_URL��ύX���܂��B


4. �R���p�C��
=============

�ȉ��ŃR���p�C������܂�

  $ make

���O��Ԃ̎��ʎq�Ƃ��� "http://example.com/SimulinkModel" ���g�p���Ă�
�܂��B�����ύX����ꍇ�AMakefile��SIM_URL��ύX���� make ���Ȃ����Ă�
�������B

���O��Ԃ�ύX����ƈȉ��̃t�@�C�����ύX����܂��B

  SimulinkModel.xsd
  SimulinkModel_ns.h

��L�ɂ��A�ȉ��̃t�@�C�����e�����󂯂܂��B

  xsd_driver.cxx    (SimulinkModel_ns.h���C���N���[�h)
  SimulinkRTW.h     (SimulinkModel_ns.h���C���N���[�h)
  SimulinkRTW.cxx   (SimulinkRTW.h�Ɉˑ�)
  SimulinkModel.cxx (SimulinkModel.xsd���琶��)
  SimulinkModel.hxx (SimulinkModel.xsd���琶��)
  

5. �e�X�g
=========

�ȉ���(�f�t�H���g�ł�pid��)�e�X�g�ł��܂��B

  $ make test

�e�X�g�Ώۂ�ύX����ꍇ�ATEST_TARGET�}�N����ݒ肵�܂��B

  $ make TEST_TARGET=test1

���� pid, test1, cell, testmux ���w��ł��܂����Acell�̓G���[�ɂȂ�܂��B

���͈ȉ��̒ʂ�ł��B

�Ecell��XML��output�^�O��connect���Ȃ���肪����G���[
�E�u���b�N������v���Ȃ����

�Ȃ��A���\���t���u���b�N���x���\��XML���o�͂���e�X�g��P�ƂŎ��s����
�ꍇ�A�ȉ��̂悤�ɂ��Ă��������B(6.1.�ɋL�ڂ�yy.xml���K�v�ł�)

  $ make test_blxml


6. ���ʊm�F
===========

6.1. �o��XML
============

�T���v���v���O���� rtw_test �ɂ����RTW-EC�̃R�[�h�𒊏o����XML�t�@�C��
�𐶐����܂�(TEST_TARGET��)�B�A�E�g�v�b�g�͈ȉ��̂��̂ł��B

  Simulink_XSD/models/pid/yy.xml
  (Simulink_XSD/models/cell/yy.xml) -- �����ł��Ȃ�
  Simulink_XSD/models/test1/yy.xml
  Simulink_XSD/models/testmux/yy.xml

���s�ɂ������ẮA���͂ƂȂ�XML�t�@�C���Ɠ����f�B���N�g����
SimulinkModel.xsd ��u���K�v������܂��B

�ȉ��ɊȒP��XML�̃^�O�̐������܂��B���e�ɂ��Ă�SimulinkXSD.xslx�A
SimulinkModel.xsd���Q�Ƃ��Ă��������B

<sm:blocks> �u���b�N���܂Ƃ߂�^�O�ł��Bsm�͖��O��Ԃ�prefix�ł��B

<block> �u���b�N�������܂��B�����͈ȉ��̒ʂ�ł�
   blocktype - �^�C�v
   name -- ���O

<output> �o�͂�line/port�������܂��B

<input> ���͂�line/port�������܂��B

  <connect> output/input�̐ڑ���block��port�������܂��B

<var> �ϐ����ł��Bmode��(�O��)���o�͂����ʁAtype�Ō^�Aname�����O�ł�

<state> ��ԕϐ��ł��Bname�Ŗ��O�Atype�Ō^�Astorage���\���̖��ł�

<param> �p�����^�ł��B(��ԕϐ��Ɠ��l)

<const_param> �萔�p�����^�ł�(����)

<code> C/Header�̃R�[�h��ێ����܂��Btype�ŃR�[�h�̎�ʂ������܂��B
  task -- �^�X�N���s���ƂȂ�R�[�h�ł�
  update -- UnitDelay�̃R�[�h�ł�
  init -- �^�X�N���s���Ɋւ�鏉�����R�[�h�ł�
  state -- ��ԕϐ��̏������R�[�h�ł�
  param -- �p�����^�̏����l�ł�
  const -- �萔�p�����^�̏����l�ł�

<forward> -- �T�u�u���b�N�Ԃ̐ڑ���������������ˑ��t���[�̃u���b�N�ł�
             �܂��A�ˑ�����ϐ�������� <var> �^�O�Ƃ��Ċ܂݂܂��B
  block -- �ڑ�����u���b�N��
  type -- �ڑ���ʂŁA���� data/event/port ������܂�

<backward> -- �T�u�u���b�N�Ԃ̐ڑ������������O���ˑ��t���[�̃u���b�N�ł�
  (forward�Ɠ���)


6.2. graphviz (dot�`��)
=======================

��L�Aforward/backward�����Ƀe�X�g�R�[�h xml_test �� xml_test.dot ��
�����܂�(TEST_TARGET���ɐ������܂�)�B�����p����ƕϐ��E�u���b�N�̐ڑ�
�֌W�����o�I�Ɋm�F�ł��܂��B

  Simulink_XSD/models/pid/test_xml.dot
  Simulink_XSD/models/pid/test_xml.png

  (Simulink_XSD/models/cell/test_xml.dot) -- �����ł��Ȃ�

  Simulink_XSD/models/test1/test_xml.dot
  Simulink_XSD/models/test1/test_xml.png

  Simulink_XSD/models/testmux/test_xml.dot
  Simulink_XSD/models/testmux/test_xml.png


6.3. ���\�t���u���b�N���x���\��XML(BLXML)
=========================================

��L�̏o��XML�̃u���b�N��RTW�̃R�[�h�f�Ђ̐��\�l(�T�C�N����)���o�͂���
���\�t��BLXML�𐶐����܂�(TEST_TARGET���ɐ������܂�)�B

  Simulink_XSD/models/pid/test_blxml.xml
  Simulink_XSD/models/test1/test_blxml.xml
  Simulink_XSD/models/testmux/test_blxml.xml

���\�l�̓u���b�N����<performance>�^�O�̑����Ƃ��ċL�ڂ���܂��B���\�l�́A
�R�[�h�̎�ޖ�(task,update,init)�Ɍv������܂�

���̃e�X�g�����{�����A�P�Ƃł̂��̐����菇�� make test_blxml �Ƃ��܂��B


7. ���[�U�K�C�h(���T��)
=======================

7.1. �f�[�^�o�C���f�B���O(SimulinkModel)
========================================

XSD�ɂ����SimulinkModel.xsd���� SimulinkModel.hxx, SimulinkModel.cxx
����������܂��B�����̎g�����ɂ��Ă͐����R�[�h�����doxygen���Q�Ƃ�
�������B���O���(namespace)�� SimulinkModel::XSD �ł��B

�T���v���R�[�h�Ƃ��� xsd_driver.cxx ������܂��̂ŁA�Q�l�ɂ��Ă��������B

���s�ɂ������ẮA���͂ƂȂ�XML�t�@�C���Ɠ����f�B���N�g����
SimulinkModel.xsd ��u���K�v������܂��B


7.2 SimulinkXML
===============

SimulinkXML.h, SimulinkXML.cxx��XSD�ɂ�萶�������f�[�^�o�C���f�B���O
�̗��p���ȒP�Ɏx�����郂�W���[���ł��B�A�z�z���p�����ȉ��̋@�\������
�܂��B���O���(namespace)�� Simulink::XML �ł��B

�E�u���b�N���̃T�[�`
  Reader�N���X�ł̓u���b�N�����L�[�Ƃ����A�z�z��(map)�ɂȂ��Ă��邽�߁A
  �u���b�N������u���b�N�����T�[�`���邱�Ƃ��\�ł��B

�Einput/output�̐ڑ���̃T�[�`

  input/output�̃u���b�N���Aline���Aport���̓|�[�g�����L�[�Ƃ����A�z�z
  ��(multimap)�ɂȂ��Ă��܂��B����𗘗p�����T�[�`�֐����p�ӂ���Ă���A
  input/output�ɕt������connect��line,port���w�肵�A����ɐڑ���������
  �̃u���b�N�̃^�O��output/input�̃^�O��T�������ł��܂��B

�� C�̊O�������P�[�W�̊֐��͖������ł�

�T���v���R�[�h�Ƃ��ẮAxml_test.cxx �ł��B�����block��
forward/backward������graphviz��dot�t�@�C���𐶐����܂�

���s�ɂ������ẮA���͂ƂȂ�XML�t�@�C���Ɠ����f�B���N�g����
SimulinkModel.xsd ��u���K�v������܂��B


8. ��������
===========

�Eglobal states�ɂ͑Ή����Ă��܂���
�Estep�֐��ŁASimulink�̃u���b�N�������E��������铙�̌��ʁAif���⃋�[
  �v���Ȃǂ�C�̍\���u���b�N�̒���Simulink�̃u���b�N�������Ă���ꍇ���A
  �������R�[�h���؂�o���Ȃ��ꍇ������܂��B
�Einitialize�֐��ł́A�������R�[�h�́A�P��ϐ����邢�͔z��v�f�̏������A
  ���[�v�ɂ��z��̏������Amemset()�ɂ�鏉�����ɑΉ����Ă��܂����A��
  �蕡�G�ȃR�[�h�̏ꍇ�A�������R�[�h���������؂�o���Ȃ��ꍇ������܂��B
�E�ϐ��̌^�ŁA�\���̂��g���悤�Ȃ��̂́A�\���̂̌^�̐؂�o���͍s���܂�
  ��̂ŁAC�̃R�[�h�������s���ꍇ�A�ʓr�A�\���̂��`����Ȃǂ̑Ή����K
  �v�ł��B
�EDemux�� p=n �ŁA�z��T�C�Y�ƕ���������v������̂̂ݎ�舵���܂�
�ESimulink�̃��f����Inport/Outport/Demux/Mux�݂̂�F�����A�������܂�
  ����ϐ��̓`�d��ǐՂ��܂����A����ȊO�̃u���b�N��<input>/<output>��
  �����g�p���܂��B���������āA��L�u���b�N�^�C�v�ȊO�Ńu���b�N�ŐM��
  ��ϐ��ɕω�������ꍇ�A�ǐՂł��Ȃ��P�[�X�������܂��B
�EConstant�͓Ɨ������u���b�N�Ƃ��Ď�舵���܂�(���̃u���b�N�ƌ������邱
  �Ƃ͂Ȃ�)�B
�E�ł��O���ɂ���Inport/Outport�͊J�n�E�I�[�̃u���b�N�Ƃ��Ďg�p���܂��B


�ȏ�
