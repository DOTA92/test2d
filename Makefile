FFTW_INC = -I/soft/library/fftw-3.3.5-gnu-serial/include

FFTW_LIB = -L/soft/library/fftw-3.3.5-gnu-serial/lib -lfftw3



all: hom_accel_2D_elas

hom_accel_2D_elas: geom.cpp period.cpp hom_proc_2D_elas.cpp hom_accel_2D_elas.cpp geom.h hom_header_2D_elas.h 
	g++ -std=c++98 $(FFTW_INC) hom_accel_2D_elas.cpp hom_proc_2D_elas.cpp geom.cpp  -O3 -lm -lrt -fopenmp -lfftw3 $(FFTW_LIB)  -o $@ 







