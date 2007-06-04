#!/bin/bash

texi2dvi b3d-doc.tex || echo "!! texi2dvi ERROR!";
dvipdf b3d-doc.dvi || echo "!! dvipdf ERROR!";

