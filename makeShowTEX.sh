#!/bin/bash

echo "\documentclass{beamer}" > Show.tex
echo "\usepackage{graphicx}" >> Show.tex
echo "%\usepackage[1in]{geometry}" >> Show.tex
echo "\usepackage{verbatim}" >> Show.tex
echo " " >> Show.tex
echo "\begin{document}" >> Show.tex

for X in `cat list.mer`
do
    echo " " >> Show.tex
    echo "\begin{frame}" >> Show.tex
    echo "${X} (\$x=2.0\$)" >> Show.tex
    echo "\\\\\\vspace{1em}" >> Show.tex
    echo "\begin{tabular}{ccc}" >> Show.tex
    echo "  \$y=9999\$&" >> Show.tex
    echo "  \$y=1.00\$&" >> Show.tex
    echo "  \$y=0.77\$\\\\" >> Show.tex
    echo "  \includegraphics[width=0.32\textwidth,height=6em]{{XPYB0_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.32\textwidth,height=6em]{{XPYB1_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.32\textwidth,height=6em]{{XPYB2_${X}}.pdf}" >> Show.tex
    echo "  \\\\" >> Show.tex
    echo "  \$y=0.5\$&" >> Show.tex
    echo "  \$y=0.4\$&" >> Show.tex
    echo "  \$y=0.3\$" >> Show.tex
    echo "  \\\\" >> Show.tex
    echo "  \includegraphics[width=0.32\textwidth,height=6em]{{XPYB3_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.32\textwidth,height=6em]{{XPYB4_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.32\textwidth,height=6em]{{XPYB5_${X}}.pdf}" >> Show.tex
    echo "\end{tabular}" >> Show.tex
    echo "\end{frame}" >> Show.tex
    echo "\begin{frame}" >> Show.tex
    echo "${X} (\$y=0.5\$)" >> Show.tex
    echo "\\\\\\vspace{1em}" >> Show.tex
    echo "\begin{tabular}{cccc}" >> Show.tex
    echo "  \$x=0.40\$&" >> Show.tex
    echo "  \$x=0.67\$&" >> Show.tex
    echo "  \$x=0.80\$&" >> Show.tex
    echo "  \$x=1.00\$\\\\" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB6_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB7_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB8_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB9_${X}}.pdf}" >> Show.tex
    echo "  \\\\" >> Show.tex
    echo "  \$x=1.25\$&" >> Show.tex
    echo "  \$x=1.43\$&" >> Show.tex
    echo "  \$x=1.67\$&" >> Show.tex
    echo "  \$x=2.00\$&" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB10_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB11_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB12_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB13_${X}}.pdf}" >> Show.tex
    echo "  \\\\" >> Show.tex
    echo "  \$x=2.50\$&" >> Show.tex
    echo "  \$x=3.33\$&" >> Show.tex
    echo "  & &" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB14_${X}}.pdf}&" >> Show.tex
    echo "  \includegraphics[width=0.23\textwidth,height=4em]{{XPYB15_${X}}.pdf}&" >> Show.tex
    echo "\end{tabular}" >> Show.tex
    echo "\end{frame}" >> Show.tex
done
echo " " >> Show.tex

echo "\end{document}" >> Show.tex
