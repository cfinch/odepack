! *Examples:
! The following is a simple example problem, with the coding needed
! for its solution by DLSODE. The problem is from chemical kinetics,
! and consists of the following three rate equations:
!        dy1/dt = -.04*y1 + 1.E4*y2*y3
!        dy2/dt = .04*y1 - 1.E4*y2*y3 - 3.E7*y2**2
!        dy3/dt = 3.E7*y2**2

! on the interval from t = 0.0 to t = 4.E10, with initial conditions
! y1 = 1.0, y2 = y3 = 0. The problem is stiff.
! The following coding solves this problem with DLSODE, using 
! MF = 21 and printing results at t = .4, 4., ..., 4.E10.  It uses 
! ITOL = 2 and ATOL much smaller for y2 than for y1 or y3 because y2 
! has much smaller values.  At the end of the run, statistical 
! quantities of interest are printed.

EXTERNAL FEX, JEX
INTEGER IOPT, IOUT, ISTATE, ITASK, ITOL, IWORK(23), LIW, LRW, MF, NEQ
DOUBLE PRECISION ATOL(3), RTOL, RWORK(58), T, TOUT, Y(3)

NEQ = 3                 ! number of first-order ODE's

Y(1) = 1.D0             ! values of y(t) at t=t1
Y(2) = 0.D0
Y(3) = 0.D0

T = 0.D0                ! initial value of independent variable t
TOUT = .4D0             ! next value of independent variable t
ITOL = 2                ! 1 indicates ATOL is scalar, 2 indicates ATOL is array
RTOL = 1.D-4            ! Relative tolerance

ATOL(1) = 1.D-6         ! Absolute tolerance for each i in Y(i)
ATOL(2) = 1.D-10
ATOL(3) = 1.D-6

ITASK = 1               ! Indicates that DLSODE is to compute output values of y
ISTATE = 1              ! ISTATE=1 for first call, ISTATE=2 for subsequent calls
                        ! Automatically updated to 2 if DLSODE was successful

IOPT = 0                ! IOPT=0 for no optional inputs, IOPT=1 for optional inputs
LRW = 58                ! Length of real work array
LIW = 23                ! Length of integer work array
MF = 21                 ! Method flag.  Possible values are:
                        ! 10  Nonstiff (Adams) method, no Jacobian used.
                        ! 21  Stiff (BDF) method, user-supplied full Jacobian.
                        ! 22  Stiff method, internally generated full Jacobian.
                        ! 24  Stiff method, user-supplied banded Jacobian.
                        ! 25  Stiff method, internally generated banded Jacobian.

20  FORMAT(' At t =',D12.4,'   y =',3D14.6)

DO IOUT = 1,12
    CALL DLSODE (FEX, NEQ, Y, T, TOUT, ITOL, RTOL, ATOL, ITASK, ISTATE, IOPT, RWORK, LRW, IWORK, LIW, JEX, MF)
    WRITE(6,20)  T, Y(1), Y(2), Y(3)
    IF (ISTATE .LT. 0)  GO TO 80
    TOUT = TOUT*10.D0               ! Next time step
END DO

WRITE(6,60)  IWORK(11), IWORK(12), IWORK(13)
60  FORMAT(/' No. steps =',i4,',  No. f-s =',i4,',  No. J-s =',i4)
STOP

! error handling
80  WRITE(6,90)  ISTATE
90  FORMAT(///' Error halt.. ISTATE =',I3)
STOP
END

SUBROUTINE  FEX (NEQ, T, Y, YDOT)
    ! Set array Ydot
    INTEGER  NEQ
    DOUBLE PRECISION  T, Y(3), YDOT(3)
    YDOT(1) = -.04D0*Y(1) + 1.D4*Y(2)*Y(3)
    YDOT(3) = 3.D7*Y(2)*Y(2)
    YDOT(2) = -YDOT(1) - YDOT(3)
    RETURN
END

SUBROUTINE  JEX (NEQ, T, Y, ML, MU, PD, NRPD)
    ! Set Jacobian matrix
    INTEGER  NEQ, ML, MU, NRPD
    DOUBLE PRECISION  T, Y(3), PD(NRPD,3)
    PD(1,1) = -.04D0
    PD(1,2) = 1.D4*Y(3)
    PD(1,3) = 1.D4*Y(2)
    PD(2,1) = .04D0
    PD(2,3) = -PD(1,3)
    PD(3,2) = 6.D7*Y(2)
    PD(2,2) = -PD(1,2) - PD(3,2)

    !   Uncomment lines below to dump Jacobian values for debugging
!    DO I=1,3
!        WRITE (6,100) PD(I,1), PD(I,2), PD(I,3)
!    ENDDO
!    100  FORMAT (es12.5, ' ', es12.5, ' ', es12.5)
!
!    WRITE (6,100) Y(1), Y(2), Y(3)

    RETURN
END
