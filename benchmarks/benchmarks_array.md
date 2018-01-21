# jc::Array benchmarks

Benchmarks run on a: MacBookPro14,2   Intel(R) Core(TM) i7-7567U CPU @ 3.50GHz

# Images
_
<br/>
<img src="./images/array/timings_get_random_small.png" alt="Timings get_random_small" width="350">
<img src="./images/array/timings_get_random_large.png" alt="Timings get_random_large" width="350">
_
<br/>
<img src="./images/array/timings_sum.png" alt="Timings sum" width="350">
<img src="./images/array/timings_push_back.png" alt="Timings push_back" width="350">

# Tables

### report.txt

## <sub>Timings</sub> <sub>get_random_small</sub>

| <sub>counts</sub> | <sub>std::vector</sub> | <sub>eastl::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> |
|--------:|-------------|---------------|---------------|------------|
| <sub>100000</sub> | <sub>0.8301</sub> <sub>ms</sub> | <sub>0.8076</sub> <sub>ms</sub> | <sub>0.8070</sub> <sub>ms</sub> | <sub>0.8073</sub> <sub>ms</sub> |
| <sub>200000</sub> | <sub>1.7399</sub> <sub>ms</sub> | <sub>1.6838</sub> <sub>ms</sub> | <sub>1.7015</sub> <sub>ms</sub> | <sub>1.6502</sub> <sub>ms</sub> |
| <sub>300000</sub> | <sub>2.9307</sub> <sub>ms</sub> | <sub>2.8138</sub> <sub>ms</sub> | <sub>2.7659</sub> <sub>ms</sub> | <sub>2.8229</sub> <sub>ms</sub> |
| <sub>400000</sub> | <sub>3.8769</sub> <sub>ms</sub> | <sub>3.9701</sub> <sub>ms</sub> | <sub>3.9898</sub> <sub>ms</sub> | <sub>4.3189</sub> <sub>ms</sub> |
| <sub>500000</sub> | <sub>5.5413</sub> <sub>ms</sub> | <sub>6.2926</sub> <sub>ms</sub> | <sub>5.8681</sub> <sub>ms</sub> | <sub>5.9643</sub> <sub>ms</sub> |
| <sub>600000</sub> | <sub>9.0944</sub> <sub>ms</sub> | <sub>9.5409</sub> <sub>ms</sub> | <sub>9.5429</sub> <sub>ms</sub> | <sub>8.6863</sub> <sub>ms</sub> |
| <sub>700000</sub> | <sub>12.0396</sub> <sub>ms</sub> | <sub>12.0469</sub> <sub>ms</sub> | <sub>11.8891</sub> <sub>ms</sub> | <sub>12.1188</sub> <sub>ms</sub> |
| <sub>800000</sub> | <sub>15.0395</sub> <sub>ms</sub> | <sub>15.5296</sub> <sub>ms</sub> | <sub>15.0654</sub> <sub>ms</sub> | <sub>14.9511</sub> <sub>ms</sub> |
| <sub>900000</sub> | <sub>17.9646</sub> <sub>ms</sub> | <sub>16.7328</sub> <sub>ms</sub> | <sub>18.1123</sub> <sub>ms</sub> | <sub>17.7658</sub> <sub>ms</sub> |
| <sub>1000000</sub> | <sub>20.4299</sub> <sub>ms</sub> | <sub>20.8780</sub> <sub>ms</sub> | <sub>21.0526</sub> <sub>ms</sub> | <sub>20.3419</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_random_large</sub>

| <sub>counts</sub> | <sub>std::vector</sub> | <sub>eastl::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> |
|--------:|-------------|---------------|---------------|------------|
| <sub>100000</sub> | <sub>3.0351</sub> <sub>ms</sub> | <sub>1.9380</sub> <sub>ms</sub> | <sub>2.0532</sub> <sub>ms</sub> | <sub>2.0162</sub> <sub>ms</sub> |
| <sub>200000</sub> | <sub>4.6583</sub> <sub>ms</sub> | <sub>4.5259</sub> <sub>ms</sub> | <sub>4.7128</sub> <sub>ms</sub> | <sub>4.7252</sub> <sub>ms</sub> |
| <sub>300000</sub> | <sub>8.1514</sub> <sub>ms</sub> | <sub>7.9548</sub> <sub>ms</sub> | <sub>8.0221</sub> <sub>ms</sub> | <sub>7.7666</sub> <sub>ms</sub> |
| <sub>400000</sub> | <sub>12.6710</sub> <sub>ms</sub> | <sub>14.0151</sub> <sub>ms</sub> | <sub>12.6651</sub> <sub>ms</sub> | <sub>12.4697</sub> <sub>ms</sub> |
| <sub>500000</sub> | <sub>18.3889</sub> <sub>ms</sub> | <sub>18.5854</sub> <sub>ms</sub> | <sub>17.8200</sub> <sub>ms</sub> | <sub>17.2721</sub> <sub>ms</sub> |
| <sub>600000</sub> | <sub>23.2546</sub> <sub>ms</sub> | <sub>23.5543</sub> <sub>ms</sub> | <sub>22.9486</sub> <sub>ms</sub> | <sub>22.2995</sub> <sub>ms</sub> |
| <sub>700000</sub> | <sub>27.5151</sub> <sub>ms</sub> | <sub>28.0592</sub> <sub>ms</sub> | <sub>27.5168</sub> <sub>ms</sub> | <sub>27.1755</sub> <sub>ms</sub> |
| <sub>800000</sub> | <sub>32.0440</sub> <sub>ms</sub> | <sub>32.6445</sub> <sub>ms</sub> | <sub>32.1771</sub> <sub>ms</sub> | <sub>32.2110</sub> <sub>ms</sub> |
| <sub>900000</sub> | <sub>36.4793</sub> <sub>ms</sub> | <sub>35.8226</sub> <sub>ms</sub> | <sub>36.1838</sub> <sub>ms</sub> | <sub>36.2182</sub> <sub>ms</sub> |
| <sub>1000000</sub> | <sub>40.9676</sub> <sub>ms</sub> | <sub>40.9470</sub> <sub>ms</sub> | <sub>40.3537</sub> <sub>ms</sub> | <sub>39.9463</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>sum</sub>

| <sub>counts</sub> | <sub>std::vector</sub> | <sub>eastl::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> |
|--------:|-------------|---------------|---------------|-----------|
| <sub>100000</sub> | <sub>0.0327</sub> <sub>ms</sub> | <sub>0.0248</sub> <sub>ms</sub> | <sub>0.0278</sub> <sub>ms</sub> | <sub>0.0276</sub> <sub>ms</sub> |
| <sub>200000</sub> | <sub>0.0647</sub> <sub>ms</sub> | <sub>0.0619</sub> <sub>ms</sub> | <sub>0.0645</sub> <sub>ms</sub> | <sub>0.0622</sub> <sub>ms</sub> |
| <sub>300000</sub> | <sub>0.0992</sub> <sub>ms</sub> | <sub>0.1087</sub> <sub>ms</sub> | <sub>0.1008</sub> <sub>ms</sub> | <sub>0.1003</sub> <sub>ms</sub> |
| <sub>400000</sub> | <sub>0.1428</sub> <sub>ms</sub> | <sub>0.1435</sub> <sub>ms</sub> | <sub>0.1418</sub> <sub>ms</sub> | <sub>0.1426</sub> <sub>ms</sub> |
| <sub>500000</sub> | <sub>0.1853</sub> <sub>ms</sub> | <sub>0.1866</sub> <sub>ms</sub> | <sub>0.1857</sub> <sub>ms</sub> | <sub>0.1850</sub> <sub>ms</sub> |
| <sub>600000</sub> | <sub>0.2323</sub> <sub>ms</sub> | <sub>0.2459</sub> <sub>ms</sub> | <sub>0.2334</sub> <sub>ms</sub> | <sub>0.2336</sub> <sub>ms</sub> |
| <sub>700000</sub> | <sub>0.2758</sub> <sub>ms</sub> | <sub>0.2727</sub> <sub>ms</sub> | <sub>0.2783</sub> <sub>ms</sub> | <sub>0.2805</sub> <sub>ms</sub> |
| <sub>800000</sub> | <sub>0.3106</sub> <sub>ms</sub> | <sub>0.3326</sub> <sub>ms</sub> | <sub>0.3124</sub> <sub>ms</sub> | <sub>0.3104</sub> <sub>ms</sub> |
| <sub>900000</sub> | <sub>0.3488</sub> <sub>ms</sub> | <sub>0.3797</sub> <sub>ms</sub> | <sub>0.3507</sub> <sub>ms</sub> | <sub>0.3631</sub> <sub>ms</sub> |
| <sub>1000000</sub> | <sub>0.3839</sub> <sub>ms</sub> | <sub>0.3926</sub> <sub>ms</sub> | <sub>0.3846</sub> <sub>ms</sub> | <sub>0.3873</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>push_back</sub>

| <sub>counts</sub> | <sub>std::vector</sub> | <sub>eastl::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> |
|--------:|-------------|---------------|---------------|-----------|
| <sub>100000</sub> | <sub>0.1581</sub> <sub>ms</sub> | <sub>0.0753</sub> <sub>ms</sub> | <sub>0.1368</sub> <sub>ms</sub> | <sub>0.0405</sub> <sub>ms</sub> |
| <sub>200000</sub> | <sub>0.2768</sub> <sub>ms</sub> | <sub>0.1504</sub> <sub>ms</sub> | <sub>0.2608</sub> <sub>ms</sub> | <sub>0.0831</sub> <sub>ms</sub> |
| <sub>300000</sub> | <sub>0.4151</sub> <sub>ms</sub> | <sub>0.2326</sub> <sub>ms</sub> | <sub>0.3910</sub> <sub>ms</sub> | <sub>0.1214</sub> <sub>ms</sub> |
| <sub>400000</sub> | <sub>0.5537</sub> <sub>ms</sub> | <sub>0.3148</sub> <sub>ms</sub> | <sub>0.5212</sub> <sub>ms</sub> | <sub>0.1713</sub> <sub>ms</sub> |
| <sub>500000</sub> | <sub>0.6924</sub> <sub>ms</sub> | <sub>0.4070</sub> <sub>ms</sub> | <sub>0.6761</sub> <sub>ms</sub> | <sub>0.2343</sub> <sub>ms</sub> |
| <sub>600000</sub> | <sub>0.8321</sub> <sub>ms</sub> | <sub>0.5474</sub> <sub>ms</sub> | <sub>0.7888</sub> <sub>ms</sub> | <sub>0.2853</sub> <sub>ms</sub> |
| <sub>700000</sub> | <sub>0.9707</sub> <sub>ms</sub> | <sub>0.5876</sub> <sub>ms</sub> | <sub>0.9420</sub> <sub>ms</sub> | <sub>0.3613</sub> <sub>ms</sub> |
| <sub>800000</sub> | <sub>1.1094</sub> <sub>ms</sub> | <sub>0.6127</sub> <sub>ms</sub> | <sub>1.0515</sub> <sub>ms</sub> | <sub>0.3652</sub> <sub>ms</sub> |
| <sub>900000</sub> | <sub>1.2480</sub> <sub>ms</sub> | <sub>0.6900</sub> <sub>ms</sub> | <sub>1.1768</sub> <sub>ms</sub> | <sub>0.4018</sub> <sub>ms</sub> |
| <sub>1000000</sub> | <sub>1.3852</sub> <sub>ms</sub> | <sub>0.7662</sub> <sub>ms</sub> | <sub>1.3047</sub> <sub>ms</sub> | <sub>0.4477</sub> <sub>ms</sub> |


