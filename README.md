# cpu-scheduler-simulater

  ## implemented Algorithms
      1) FCFS
      2) SJF
      3) SRTF
      4) PS
      5) RR
      6) MFQ
      7) HRN
  
  ## input value
    {algorithm} {process cores} -b {n} {n} ... -a {n} {n} ... -pr {n} {n} ... -t {n} {n} ...

  ## options (not optioned -> random value)
     : -b = burst time for each processes
     : -a = arriving time for each processes
     : -pr = priority (PS required)
     : -t = time quantum (RR required)

  ### input example 
      : FCFS 5 -b 2 3 10 14 11 -a 0 0 0 0 0
      : RR 3 -b 2 3 10 -a 0 2 4 -t 5
      : PS 3 -pr 3 2 1
