
Questions
=========

Norm
----


* Look through the code for ``run()`` in ``norm_utils.hpp``.  How are we setting the number of threads for OpenMP to use?

#ifdef _OPENMP
    omp_set_num_threads(nthreads);
#endif

* Which version of ``norm`` provides the best parallel performance?  How do the results compare to the parallelized versions of ``norm`` from ps5?

The best performing version was norm_block_critical which was a little surprising to me. I assumed that the block reduction and the par for would be better. That wasn't correct. I didn't expect the cyclic version to outperform the others and it was inline with my expectations. As explained in ps5, what might be causing the cyclic version to not be so fast is that: Different strides require page faults. This is less common when the thread count is small, but will def increase with with adding more and more threads.

shehios-MBP:norm shehio$ ./norm_block_critical.exe
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576      5.1701     5.48002     11.2987     20.7337      28.731             0   5.19496e-15   5.00255e-15   4.04052e-15
     2097152     4.69061     4.76805     7.22019     6.60671     5.34829             0   6.80033e-16   1.08805e-15   2.72013e-15
     4194304     4.29103     4.39232     5.15572     4.12665     4.20292             0   4.80808e-15   5.57737e-15   3.84646e-15
     8388608     4.51972     4.35998     4.55903     3.94202     3.97942             0   1.11505e-14   9.92669e-15   9.51874e-15
    16777216     4.39725     4.30185     4.38841     3.65333     3.95833             0   9.61626e-15   7.88533e-15   4.23115e-15
    33554432      4.0778     3.80682     3.96089      3.8192     4.20934             0   9.65326e-15   1.12848e-14   9.78922e-15

shehios-MBP:norm shehio$ make norm_block_reduction.exe && ./norm_block_reduction.exe
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.13053     4.52966     7.34003     11.6928     11.6253             0   5.19496e-15   5.00255e-15   4.23293e-15
     2097152     4.12583     2.78465      5.1311     6.31767     4.52272             0   6.80033e-16   1.08805e-15   2.58412e-15
     4194304     4.29103     4.51837     5.73339     4.63082     4.40176             0   4.80808e-15   5.57737e-15   3.84646e-15
     8388608     4.17759     4.25386      4.8771     3.97188     3.54249             0   1.11505e-14   9.92669e-15   9.65473e-15
    16777216     3.46197     4.22682     4.82531     3.94401     4.21864             0   9.61626e-15   7.88533e-15   4.23115e-15
    33554432     4.13523     4.50827     6.34814     4.27056     4.01506             0   9.65326e-15   1.12848e-14   9.78922e-15

shehios-MBP:norm shehio$ make norm_cyclic_critical.exe && ./norm_cyclic_critical.exe
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.04052     5.32055     3.97464     2.88133     5.33467             0      0.414213      0.999999       1.82842
     2097152     3.43819     4.67976      3.4092     3.67574       3.553             0      0.414214             1       1.82842
     4194304     4.06115     4.60996     4.34569     4.29103     2.85869             0      0.414214             1       1.82843
     8388608     2.52365     2.61817     4.28865     3.62829     3.76508             0      0.414214             1       1.82843
    16777216     3.77342     4.15436     4.14646      4.0019     3.76041             0      0.414214             1       1.82843
    33554432     3.42392     3.72827     4.40677     4.02194     3.51618             0      0.414214             1       1.82843

shehios-MBP:norm shehio$ make norm_cyclic_reduction.exe && ./norm_cyclic_reduction.exe
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     2.52659     3.01073     3.44969     4.45935     5.84642             0      0.414213      0.999999       1.82842
     2097152     4.42375     4.79065      4.4432     4.05955     3.34711             0      0.414214             1       1.82842
     4194304     4.67311      4.4593     3.44583     4.22025       3.833             0      0.414214             1       1.82843
     8388608     4.21962     4.40578     4.51972     4.39655     3.86216             0      0.414214             1       1.82843
    16777216     4.01664     4.27655     4.53438     4.37082     3.89471             0      0.414214             1       1.82843
    33554432     3.99458     4.30974     4.52565     4.41506     3.84421             0      0.414214             1       1.82843

shehios-MBP:norm shehio$ make norm_parfor.exe && ./norm_parfor.exe
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576      4.8579     4.52966     4.67714     4.33442     4.84619             0             0             0             0
     2097152     4.85975     4.99174     4.96721     4.97944     4.84809             0             0             0             0
     4194304     4.57902     4.60996     4.63082     4.57902     4.50841             0             0             0             0
     8388608     4.22813     4.33296     4.32402     4.43373     4.48109             0             0             0             0
    16777216     4.14646     4.31035     4.37959     4.21864     4.33606             0             0             0             0
    33554432     4.20181     4.00138     4.14984     4.23209     4.28615             0             0             0             0


* Which version of ``norm`` provides the best parallel performance for larger problems (i.e., problems at the top end of the default sizes in the drivers or larger)?  How do the results compare to the parallelized versions of ``norm`` from ps5?
When it comes to bigger sizes, the 2-thread block reduction outperforms all of them, not by much nonetheless. They all stagnate at around 4 GFLOPS. The other ones are inconclusive.
Comparing them to PS5, they're slightly better. This might be because openmp is better in allocating threads than a lay person.

PS5 results

pnorm
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.84293     5.52365     9.27364     10.6403     10.6403             0             0   1.92318e-16             0
     2097152     3.98214     3.61629     5.04143     4.43035      4.0451             0   5.43881e-16   4.07911e-16   9.51792e-16
     4194304     3.79919     3.55449     4.04856     3.42672     3.43795             0    9.6159e-16   1.92318e-16   5.76954e-16
     8388608       3.813     3.59907     3.90867     3.54065     3.59907             0    1.3595e-16   6.79751e-16             0
    16777216     3.60247     3.21755      3.7884     3.51618     3.64722             0   3.84567e-16   1.34599e-15   3.84567e-16
    33554432     3.87913      3.6873       3.813     3.65716     3.95923             0   7.20652e-15   7.61444e-15   6.66264e-15

fnorm
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.05414     5.34829     9.91007     11.6187     11.4867             0             0   1.92318e-16             0
     2097152     4.26421     3.92111     5.06639      4.1943     3.90615             0   5.43881e-16   4.07911e-16   9.51792e-16
     4194304     3.67921     3.46065     3.98698     3.46065     3.48364             0    9.6159e-16   1.92318e-16   5.76954e-16
     8388608     3.62299     3.42931     3.78652      3.3658     3.56379             0    1.3595e-16   5.43801e-16             0
    16777216     3.65858     3.54805       3.813     3.67002     3.91468             0   3.84567e-16   1.34599e-15   3.84567e-16
    33554432     3.62751     3.41521     4.12978     3.70767     3.89037             0   7.20652e-15   7.61444e-15   6.66264e-15

cnorm
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     6.82991     1.65981     2.76939     3.15884     3.96403   1.65393e-14   1.00005e-14    9.6159e-16   2.30782e-15
     2097152     4.67311     1.31375     2.36353     2.62413     3.21827   8.15822e-15    8.7021e-15   4.21508e-15   4.89493e-15
     4194304      2.7962     1.23072      2.7962     3.64089     3.21649   3.82713e-14   3.07709e-15   2.69245e-15   2.30782e-15
     8388608     3.29462     1.51461     2.48977     4.17823     3.77342   1.41388e-14   1.22355e-15    2.1752e-15   7.34131e-15
    16777216     4.06369     1.54324      2.7962     3.98103       4.092   4.74941e-14   1.17293e-14   2.26895e-14   3.84567e-15
    33554432     3.57914     1.53392     2.77883     4.01849     3.56962   1.61807e-14     2.937e-14   1.31893e-14   7.47847e-15

rnorm
c++ -std=c++17  -Ofast -march=native -DNDEBUG   -Wall rnorm.o amath583.o amath583IO.o amath583sparse.o -o rnorm.exe 
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
     1048576     5.43456     4.70152     4.65819     5.21045     5.10519             0             0   1.92318e-16             0
     2097152     4.06115      4.5688     5.16874     5.41487     4.99224             0   5.43881e-16   4.07911e-16   9.51792e-16
     4194304      4.1943       3.813     4.76625     4.06425     3.66635             0    9.6159e-16   1.92318e-16   5.76954e-16
     8388608     4.00926     3.78652      4.3447     3.92273     3.86709             0    1.3595e-16   5.43801e-16             0
    16777216     4.00821     3.86317      4.3336     3.90168     3.99458             0   3.84567e-16   1.34599e-15   1.92284e-16
    33554432     4.01849     3.89037     4.48889     3.99458     4.07957             0   7.20652e-15   7.61444e-15   6.66264e-15

* Which version of ``norm`` provides the best parallel performance for small problems (i.e., problems smller than the low end of the default sizes in the drivers)?  How do the results compare to the parallelized versions of ``norm`` from ps5?

Again, norm block critical is phenomonal as it maxes at 46 GFLOPS for N = 524288. Except for norm block reduction, nothing really comes near such performance. To compare to different implementations from PS5, fnorm is best for smaller sizes but only maxes at 12 GFLOPS for the same N = 524288.

shehios-MBP:norm shehio$ make norm_block_critical.exe && ./norm_block_critical.exe 16384 33554432
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
       16384     3.21058     6.27019     8.96947     13.6999     10.5273   3.86194e-16   1.93097e-16   1.93097e-16   1.93097e-16
       32768     13.2474      7.1187     13.2474     20.4118     18.8713   6.81632e-16   1.36326e-16             0   1.36326e-16
       65536     25.0085     7.35545     14.1892     24.3986     28.1786   3.84025e-16             0             0   1.92012e-16
      131072     35.1135     7.27807     14.5034     26.6863     37.7636   2.72185e-16   1.36092e-16   2.72185e-16             0
      262144     35.1365     7.23025     14.9461     28.6111     45.5177   9.61938e-16   5.77163e-16             0             0
      524288     26.3938     6.47073     12.3823     26.7457     46.6494   1.49664e-15   1.49664e-15             0             0
     1048576     11.2356     4.74332     9.26806     15.9617      18.796   2.50111e-15   1.15436e-15   9.61965e-16   1.92393e-16

shehios-MBP:norm shehio$ make norm_block_reduction.exe && ./norm_block_reduction.exe 16384 33554432
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
       16384      2.5351     5.15513     5.95295     7.40812     9.43487   3.86194e-16   1.93097e-16   1.93097e-16   1.93097e-16
       32768     12.7411     5.34854     9.75783     20.0036     27.7827   6.81632e-16   1.36326e-16             0             0
       65536     24.3986     6.17495     12.9076     25.9829     33.9099   5.76037e-16   1.92012e-16   1.92012e-16             0
      131072     25.6599     6.41497     12.2041     23.5467     42.5845   2.72185e-16   1.36092e-16   2.72185e-16             0
      262144     32.8325      6.0507     14.6188     27.0646     30.3452   9.61938e-16   5.77163e-16             0             0
      524288     17.5958     3.93319      8.0237     21.5691     33.9987   1.49664e-15   1.49664e-15             0             0
     1048576     12.5698     4.53988     8.01262     11.1114     10.9303   2.50111e-15   1.15436e-15   9.61965e-16   1.92393e-16

shehios-MBP:norm shehio$ make norm_parfor.exe && ./norm_parfor.exe 16384 33554432
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
       16384     3.43676     5.88292     4.89044     5.69855     6.02467   5.79292e-16   5.79292e-16   5.79292e-16   5.79292e-16
       32768     13.4252     6.69015     3.89174     4.96366     6.17394   5.45306e-16   5.45306e-16   5.45306e-16   5.45306e-16
       65536     18.0242     6.73631     6.66894     6.13706     6.02615   3.84025e-16   3.84025e-16   3.84025e-16   3.84025e-16
      131072     25.3351     5.78459     5.75135     5.95675     6.08349   2.72185e-16   2.72185e-16   2.72185e-16   2.72185e-16
      262144     23.2881     6.25869     7.50105      7.0273     6.69826   9.61938e-16   9.61938e-16   9.61938e-16   9.61938e-16
      524288     29.0714     5.61884      6.3883     5.88248      5.9523   1.49664e-15   1.49664e-15   1.49664e-15   1.49664e-15
     1048576     9.76296     4.53988     5.63353     4.40081     4.07119   2.30872e-15   2.30872e-15   2.30872e-15   2.30872e-15

shehios-MBP:norm shehio$ make norm_cyclic_critical.exe && ./norm_cyclic_critical.exe 16384 33554432
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
       16384     5.14188     6.99368       6.558     5.97072     4.66245   5.79292e-16      0.414178       0.99991       1.82813
       32768     17.7023     7.16973      7.1187      6.7352     5.33428   6.81632e-16      0.414213      0.999994       1.82832
       65536     25.6498     7.35545     7.38259      7.1453     5.66766   5.76037e-16      0.414211       0.99999       1.82837
      131072     32.2818     7.19953     7.52432     7.27807     5.99242   2.72185e-16      0.414211       0.99998       1.82837
      262144     33.3797     6.97833     7.50105     7.39033     5.94297   9.61938e-16      0.414213      0.999998       1.82842
      524288     29.9392     6.24899     6.75396     7.06312     5.74764   1.49664e-15      0.414213      0.999999       1.82842
     1048576     14.4688     4.65548      4.8579     4.63403     4.84619   2.50111e-15      0.414213      0.999998       1.82842

shehios-MBP:norm shehio$ make norm_cyclic_reduction.exe && ./norm_cyclic_reduction.exe 16384 33554432
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
       16384     3.23656     6.19254     4.89044     4.83138     5.34811   3.86194e-16      0.414178       0.99991       1.82813
       32768     16.6696     5.46545     5.30598     5.90075     3.92227   5.45306e-16      0.414213      0.999994       1.82832
       65536     21.0598     5.73262     7.22268     7.17091     5.79908   3.84025e-16      0.414211       0.99999       1.82837
      131072     29.8727      7.0227     5.65387     6.60551     5.40938   2.72185e-16      0.414211       0.99998       1.82837
      262144     33.3797     5.25664      3.4412     5.87326     4.66849   9.61938e-16      0.414213      0.999998       1.82842
      524288     41.7901     6.15315     5.88248     6.13433     5.86528   1.49664e-15      0.414213      0.999999       1.82842
     1048576     17.3377     4.82295     4.97814     4.94145     4.68804   2.50111e-15      0.414213      0.999998       1.82842

PS5
shehios-MBP:ps5b shehio$ make pnorm.exe && ./pnorm.exe 16384 33554432
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
       16384      18.185     1.03111    0.956193    0.591471    0.277596             0             0   1.91735e-16   1.91735e-16
       32768     14.2906     1.97696     1.94619      1.2891    0.534085             0   2.72281e-16   2.72281e-16   2.72281e-16
       65536     10.6461     2.87567     2.75684     1.69904     1.04352             0   1.92544e-16   1.92544e-16   1.92544e-16
      131072     9.53705     2.69916     5.78838     4.31634     1.89299             0             0             0             0
      262144     11.0216     7.96002     9.46191     8.42826      5.1434             0   3.84632e-16   1.92316e-16             0
      524288     12.7289     7.44877     9.66908     6.98322     5.43559             0   1.22329e-15   5.43686e-16   4.07764e-16
     1048576     4.65819     5.07953     6.16358     5.64708     6.60671             0   1.92315e-16             0   1.92315e-16

shehios-MBP:ps5b shehio$ make fnorm.exe && ./fnorm.exe 16384 33554432
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
       16384     19.2342     1.04621    0.949836    0.679007    0.346682             0             0   1.91735e-16   1.91735e-16
       32768     17.2473     2.34272     2.07971     1.05856    0.671821             0   2.72281e-16   2.72281e-16   2.72281e-16
       65536     13.5234     3.98699     3.89391     2.53994     1.26675             0   1.92544e-16   1.92544e-16   1.92544e-16
      131072     13.0051     5.41292     6.25869      4.6147     2.48484             0             0             0             0
      262144     12.2313     7.16402     9.28669     7.42936     2.44625             0   3.84632e-16   1.92316e-16             0
      524288     2.92321     6.13161     10.9303     12.5698     8.89898             0   1.22329e-15   5.43686e-16   4.07764e-16
     1048576     4.41409     3.50982     7.06872     7.16899     9.18934             0   1.92315e-16             0   1.92315e-16
     2097152     3.93619     3.42278     4.58928     4.48864     4.31819             0   6.79973e-16   9.51962e-16   1.35995e-15
     4194304     3.70522     3.29741     4.24525     3.95689     3.28707             0   3.84617e-16   5.76926e-16   1.92309e-16
     8388608     3.77342     3.27483     4.03896     3.77342     3.47299             0   2.44693e-15   1.90317e-15   6.79702e-16
    16777216     3.56962     3.45413     3.85051     3.56962     3.68152             0    4.8073e-15   3.46126e-15   3.46126e-15
    33554432     3.71794     3.62751     4.03056     3.59833     3.66715             0    2.4474e-15   5.43866e-15   4.89479e-15

shehios-MBP:ps5b shehio$ make cnorm.exe && ./cnorm.exe 16384 33554432
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
       16384     12.6605    0.575808     0.84689    0.606536    0.324733   1.15041e-15   3.83471e-16   1.91735e-16   1.91735e-16
       32768     16.1345    0.911058     1.01558     1.19801    0.580581   8.16843e-16    1.3614e-15   1.76983e-15    1.3614e-16
       65536      11.372     1.21744     2.08486      1.5094     1.08657   7.70176e-16   1.15526e-15   1.92544e-16   7.70176e-16
      131072     11.9213     1.18789     1.98295     3.19933     2.15353   8.70911e-15   1.90512e-15    4.0824e-16    2.7216e-16
      262144     11.0216     1.10947     2.77829     4.39896     3.49464   5.76948e-15   3.84632e-16    9.6158e-16   5.76948e-16
      524288     9.39798     1.40838     2.72516     4.61277     4.22514   9.92227e-15   5.16502e-15   4.07764e-16   6.79607e-16
     1048576     5.52365     1.40198     2.62553     4.26509     3.99536   8.65418e-15   1.53852e-15   7.69261e-16    3.8463e-16

shehios-MBP:ps5b shehio$ make rnorm.exe && ./rnorm.exe 16384 33554432
           N  Sequential    1 thread   2 threads   4 threads   8 threads      1 thread     2 threads     4 threads     8 threads
       16384      18.185     20.4118    0.827277     0.38321    0.187545             0             0   1.91735e-16             0
       32768     15.3899      16.399     2.03736    0.834313    0.388633             0   2.72281e-16   2.72281e-16    1.3614e-16
       65536     11.6365     12.9966      3.1371     1.66235    0.772172             0   1.92544e-16   3.85088e-16   1.92544e-16
      131072     13.0051     12.2121     6.63172     3.26186     1.50133             0             0             0             0
      262144     11.3973     10.6698     6.91699     4.16167     1.97823             0   3.84632e-16   1.92316e-16             0
      524288     8.45029     10.2611     10.8127     8.66883     4.18993             0   1.22329e-15   6.79607e-16   4.07764e-16
     1048576     4.95504     4.95504     8.42356     9.02524       5.554             0   1.92315e-16             0   1.92315e-16

Sparse Matrix-Vector Product
----------------------------

* How does ``pmatvec.cpp`` set the number of OpenMP threads to use?
#ifdef _OPENMP
    omp_set_num_threads(nthreads);
#endif

* (For discussion on Piazza.)
What characteristics of a matrix would make it more or less likely to exhibit an error 
if improperly parallelized?  Meaning, if, say, you parallelized ``CSCMatrix::matvec`` with just basic  columnwise partitioning -- there would be potential races with the same locations in ``y`` being read and written by multiple threads.  But what characteristics of the matrix give rise to that kind of problem?  Are there ways to maybe work around / fix that if we knew some things in advance about the (sparse) matrix?

One can make any method parallel. The problems arise from the fact that some implementations would clash more than others for a multi-threaded environment. So, as long that there are more benefits (performance, simplicity, modularity) than costs (complexity, locks) than it should be implemented.

Now, for the matrix problems, we don't care about the right-hand-side of the equation since many threads could read the items in the memory with no conflicts. The problems arise when the left-hand-side is being written to by many threads.
There are two solutions to that: Make sure that the work of one thread doesn't overlap with another. The other is to lock the memory written to in the left-hand-side. We certainly opt for the first solution in all our implementations.

* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?
I parallelized CSR -> matvec and CSC -> t_matvec since we can easily ensure that there's no overlap between two working threads. The only directive that I used is: #pragma omp parallel.
It seems that the max is between N = 128 and N = 256. The GFLOPS are between 6 and 7 for 4 and 8 threads, which is at least 3.4x when compared to the single threaded version. For 2 threads, the speed up is around 2x only.

shehios-MBP:matvec shehio$ make pmatvec.exe && ./pmatvec.exe
1 threads
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      16       256        1216     1.80187     2.70281     2.19789     1.49259     2.24728     2.00008
      32      1024        4992     1.39888     1.69525     1.73947     1.51545     1.73947     1.77026
      64      4096       20224     1.32541     1.85312     1.75559     1.61401     1.78693     1.81942
     128     16384       81408     1.26157     1.84027     1.84027     1.61766     1.77513     1.84027
     256     65536      326656     1.01263     1.23492     1.25016     1.20552     1.35018     1.41627
     512    262144     1308672    0.938957    0.987677     1.17633    0.997083     1.02641      1.1897
    1024   1048576     5238784     0.93044    0.975644     1.16983    0.975644     1.01681     1.12609
    2048   4194304    20963328    0.892057    0.944826     1.13699      1.0226    0.939533     1.19364
2 threads
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      16       256        1216     1.62608     2.63168     2.32567     1.60006     2.29894     2.29894
      32      1024        4992     1.38916     1.98059     3.07753     1.61322     1.90514     3.07753
      64      4096       20224      1.3708     1.92439     3.51117     1.65402     1.87044     3.45063
     128     16384       81408     1.28583     1.80711     3.64708     1.60471     1.79098     3.64708
     256     65536      326656     1.09474      1.3237     2.85249     1.22004     1.51139     2.81287
     512    262144     1308672    0.997083    0.997083     2.11503     1.08491     1.03147     2.13661
    1024   1048576     5238784    0.916289    0.876306     1.78507    0.662044    0.600958     1.13138
    2048   4194304    20963328    0.716695    0.966609     1.95008     1.00423    0.944826     1.85311
4 threads
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      16       256        1216     1.51521     2.10534       2.174     1.57486     2.22231     2.43912
      32      1024        4992     1.46014     1.96117     4.76284     1.61322     1.81854     4.65208
      64      4096       20224     1.33424     1.87044     6.67122     1.62713     1.85312     6.45602
     128     16384       81408      1.4126     1.89235      7.1639     1.59198     1.71444      7.1639
     256     65536      326656    0.880551    0.997669     2.46984     1.11893     1.19133     1.60735
     512    262144     1308672    0.438968    0.675444     2.82956      1.1965    0.872448     2.82956
    1024   1048576     5238784    0.876306     0.83675     2.05969     1.02546    0.902562      1.7337
    2048   4194304    20963328    0.586387    0.752048     1.69401    0.961069    0.818081     1.75609
8 threads
 N(Grid) N(Matrix)         NNZ         COO       COO^T         CSR       CSR^T         CSC       CSC^T
      16       256        1216     1.20487      1.7392     1.21217    0.840368     1.85192     1.10501
      32      1024        4992     1.05841     1.32476     3.92234    0.926108     1.61322     4.87901
      64      4096       20224     1.03163     1.26669     4.16951    0.981062      1.3708      4.3508
     128     16384       81408     1.17304     1.68562     4.55885    0.815404      1.4126     7.42923
     256     65536      326656     1.00261     1.19133     6.98368    0.997669     1.13143     6.98368
     512    262144     1308672    0.772648    0.906439     1.52838    0.753193    0.830903     1.88637
    1024   1048576     5238784    0.760202     0.79796     1.70911    0.667546    0.876306     1.95922
    2048   4194304    20963328    0.752048    0.904079     1.69401    0.868946    0.849147     1.72007

Sparse Matrix Dense Matrix Product (AMATH583 Only)
--------------------------------------------------
* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?  How does the parallel speedup compare to sparse matrix by vector product?
The only directive that I used is: #pragma omp parallel. I parallelized both matmat methods for CSR and CSC. My solution focuses on running a portion of the matrix on a thread safely. The portion is decided by the number of colunmns of B, so it's extremely sensitive to this number. So, if we set NRHS = 1, we won't get any improvements. We start to see improvements for NRHS = 8, since we can split them equaly on 8 threads. The results are pasted below.
The max speedup for 4 and 8 threads is 6x, while for the 2 threads, it's a little less 3x.
The speedup in this problem is way more than than that of the matrix. I suspect this has to do with the memory management.

shehios-MBP:matvec shehio$ make pmatmat.exe && ./pmatmat.exe
1 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.654176     1.59209     1.17985
     128     16384       81408       1    0.659364     1.74385     1.44057
     256     65536      326656       1    0.491176     1.21245     1.14053
     512    262144     1308672       1    0.525415     1.19777     1.03924
    1024   1048576     5238784       1    0.549643     1.09569    0.798291
    2048   4194304    20963328       1    0.521291     1.11169    0.959107
2 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.641474      1.6727      1.6314
     128     16384       81408       1    0.669355     1.74385      1.5592
     256     65536      326656       1    0.625964     1.62147     1.44712
     512    262144     1308672       1    0.622628     1.23979     1.04694
    1024   1048576     5238784       1    0.560673     1.24179    0.738507
    2048   4194304    20963328       1    0.484301      1.1979     1.01202
4 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.595242     1.28295      1.6314
     128     16384       81408       1    0.676185      1.7212     1.50605
     256     65536      326656       1    0.640868     1.49536     1.08534
     512    262144     1308672       1    0.513951     1.25077      1.1877
    1024   1048576     5238784       1    0.566355     1.32001     1.07462
    2048   4194304    20963328       1    0.555846     1.31608    0.968603
8 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       1    0.606163     1.27061     1.17985
     128     16384       81408       1    0.599693     1.39508     1.38054
     256     65536      326656       1    0.447117    0.897215     1.10313
     512    262144     1308672       1    0.584035    0.846327    0.923768
    1024   1048576     5238784       1    0.560673     1.13271    0.846672
    2048   4194304    20963328       1     0.49078    0.881341    0.968603


shehios-MBP:matvec shehio$ make pmatmat.exe && ./pmatmat.exe 8
make: `pmatmat.exe' is up to date.
1 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       8     3.69425     1.43003     1.37106
     128     16384       81408       8     4.02251     1.51962     1.35411
     256     65536      326656       8     3.44474    0.851508    0.711589
     512    262144     1308672       8     3.27168    0.712202    0.615846
    1024   1048576     5238784       8     2.97236    0.710344    0.610048
    2048   4194304    20963328       8     2.83049    0.454644     0.50514
2 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       8      3.1665     1.84713     1.29119
     128     16384       81408       8     3.10831     2.13696      1.5903
     256     65536      326656       8     3.69679     1.64748     0.98421
     512    262144     1308672       8     2.86832     1.22449    0.914356
    1024   1048576     5238784       8     3.30002     1.16742     1.06371
    2048   4194304    20963328       8     3.24071     1.39031     1.23998
4 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       8     3.69425      4.4331     1.19814
     128     16384       81408       8     4.55885     4.88448     1.98211
     256     65536      326656       8     4.09644     3.52485     1.96842
     512    262144     1308672       8     3.67347     2.86832     1.58627
    1024   1048576     5238784       8     3.27424     2.75725     2.06455
    2048   4194304    20963328       8     3.27232     2.86678     2.44381
8 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      64      4096       20224       8     3.69425     5.11512      1.2666
     128     16384       81408       8     3.90758     6.21661     2.35802
     256     65536      326656       8     3.15767     6.06274     3.29496
     512    262144     1308672       8     3.54894     5.81632     2.58503
    1024   1048576     5238784       8     3.15115     3.08164     2.30276
    2048   4194304    20963328       8     3.09137      3.2097     2.87292

shehios-MBP:matvec shehio$ make pmatmat.exe && ./pmatmat.exe 32
make: `pmatmat.exe' is up to date.
1 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      16       256        1216      32      6.9632     1.48653     1.47001
      32      1024        4992      32     7.40147     1.24511     1.09202
      64      4096       20224      32     5.90893     1.12318    0.781065
     128     16384       81408      32     4.57858    0.384461    0.328464
     256     65536      326656      32     3.54339    0.202971    0.194837
     512    262144     1308672      32     4.60192    0.210018    0.177072
    1024   1048576     5238784      32     4.39714    0.200558    0.168505
    2048   4194304    20963328      32     4.60653    0.194421    0.168915
2 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      16       256        1216      32     6.30004      1.9174    0.707491
      32      1024        4992      32     8.32666     1.82502    0.770095
      64      4096       20224      32     6.47168     1.74238    0.767826
     128     16384       81408      32     3.28464    0.609247    0.535792
     256     65536      326656      32      5.2265    0.462522    0.310639
     512    262144     1308672      32     4.27321    0.445505    0.300844
    1024   1048576     5238784      32      4.5462    0.366629    0.330002
    2048   4194304    20963328      32     4.59864    0.401512     0.37201
4 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      16       256        1216      32     6.01367     2.28105    0.707491
      32      1024        4992      32     6.66132     2.83461    0.931654
      64      4096       20224      32     6.47168     3.02012     1.18179
     128     16384       81408      32     5.81128     1.32538    0.839407
     256     65536      326656      32     5.80722    0.995523    0.643261
     512    262144     1308672      32     4.10564    0.832555    0.340191
    1024   1048576     5238784      32     4.56166    0.314745    0.524904
    2048   4194304    20963328      32     4.58685     0.37948    0.452039
8 threads   
 N(Grid) N(Matrix)         NNZ    NRHS         COO         CSR         CSC
      16       256        1216      32      6.9632     3.22685    0.994743
      32      1024        4992      32     7.01192     4.03717     1.16865
      64      4096       20224      32     6.47168     4.38404     1.56213
     128     16384       81408      32     4.57858     2.39831      1.2487
     256     65536      326656      32     5.36051     1.88342    0.889616
     512    262144     1308672      32     3.98833     1.23169     0.74915
    1024   1048576     5238784      32     4.50043     0.53304    0.472728
    2048   4194304    20963328      32     4.31053    0.390811    0.290889


PageRank Reprise
----------------

* Describe any changes you made to pagerank.cpp to get parallel speedup.  How much parallel speedup did you get for 1, 2, 4, and 8 threads?
I changed the schedule for omp, I also used a csc implementation rather than a csr one.

+  omp_set_schedule(omp_sched_static, 0);
+  CSCMatrix A = read_cscmatrix(input_file);

* (EC) Which functions did you parallelize?  How much additional speedup did you achieve?

I made parallel norm1 and norm2 parallel. Sorting can be made parallel but we opted for not doing it. As far as we know the standard implementatoin of std::swap can't be parallel, but we could have written our own parallel swap too. These additional parallelization made pagerank 1.04x faster on cit-Patents_adj.mtx, which is kind of nice when working with even larger sizes.


Before:
shehios-MBP:pagerank shehio$ make pagerank.exe && ./pagerank.exe  ./../data/cit-Patents_adj.mtx -n 8
# elapsed time [read]: 30314 ms
Converged in 37 iterations
# elapsed time [pagerank]: 7483 ms

After:
shehios-MBP:pagerank shehio$ make pagerank.exe && ./pagerank.exe  ./../data/cit-Patents_adj.mtx -n 8
# elapsed time [read]: 33332 ms
Converged in 37 iterations
# elapsed time [pagerank]: 7200 ms
# elapsed time [rank]: 358 ms

Load Balanced Partitioning with OpenMP (Extra Credit)
-----------------------------------------------------
* Are there any choices for scheduling that make an improvement in the parallel performance (most importantly, scalability) of pagerank?
From my experiments, I found that Dynamic is the best, and that static comes next. Let me show the data.

DYNAMIC == BEST
shehios-MBP:pagerank shehio$ make pagerank.exe && ./pagerank.exe  ./../data/cit-Patents_adj.mtx -n 8
# elapsed time [read]: 28747 ms
Converged in 37 iterations
# elapsed time [pagerank]: 6386 ms
# elapsed time [rank]: 333 ms


STATIC == BETTER
shehios-MBP:pagerank shehio$ make pagerank.exe && ./pagerank.exe  ./../data/cit-Patents_adj.mtx -n 8
# elapsed time [read]: 30035 ms
Converged in 37 iterations
# elapsed time [pagerank]: 6868 ms
# elapsed time [rank]: 330 ms



GUIDED === BAD
shehios-MBP:pagerank shehio$ make pagerank.exe && ./pagerank.exe  ./../data/cit-Patents_adj.mtx -n 8
# elapsed time [read]: 32660 ms
Converged in 37 iterations
# elapsed time [pagerank]: 8797 ms
# elapsed time [rank]: 391 ms