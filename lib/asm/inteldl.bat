@echo off
curl -o intelsdm.pdf -L https://cdrdv2-public.intel.com/843829/325383-sdm-vol-2abcd-dec-24.pdf
pdftotext -table -simple2 "intelsdm.pdf" sdm.txt
rem del intelsdm.pdf