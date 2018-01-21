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

| <sub>counts</sub> | <sub>std::vector</sub> | <sub>eastl::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> | <sub>carray</sub> |
|--------:|-------------|---------------|---------------|------------|------------|
| <sub>100000</sub> | <sub>0.8264</sub> <sub>ms</sub> | <sub>0.8080</sub> <sub>ms</sub> | <sub>0.8081</sub> <sub>ms</sub> | <sub>0.8070</sub> <sub>ms</sub> | <sub>0.9156</sub> <sub>ms</sub> |
| <sub>200000</sub> | <sub>1.7394</sub> <sub>ms</sub> | <sub>1.7150</sub> <sub>ms</sub> | <sub>1.6988</sub> <sub>ms</sub> | <sub>1.7306</sub> <sub>ms</sub> | <sub>1.8948</sub> <sub>ms</sub> |
| <sub>300000</sub> | <sub>3.1953</sub> <sub>ms</sub> | <sub>2.8719</sub> <sub>ms</sub> | <sub>2.7273</sub> <sub>ms</sub> | <sub>2.7776</sub> <sub>ms</sub> | <sub>2.9445</sub> <sub>ms</sub> |
| <sub>400000</sub> | <sub>4.0184</sub> <sub>ms</sub> | <sub>4.1398</sub> <sub>ms</sub> | <sub>3.8273</sub> <sub>ms</sub> | <sub>4.0719</sub> <sub>ms</sub> | <sub>4.2344</sub> <sub>ms</sub> |
| <sub>500000</sub> | <sub>5.6850</sub> <sub>ms</sub> | <sub>5.8138</sub> <sub>ms</sub> | <sub>5.6511</sub> <sub>ms</sub> | <sub>5.9827</sub> <sub>ms</sub> | <sub>6.4052</sub> <sub>ms</sub> |
| <sub>600000</sub> | <sub>8.7354</sub> <sub>ms</sub> | <sub>9.0637</sub> <sub>ms</sub> | <sub>8.4654</sub> <sub>ms</sub> | <sub>9.2994</sub> <sub>ms</sub> | <sub>9.2293</sub> <sub>ms</sub> |
| <sub>700000</sub> | <sub>10.9367</sub> <sub>ms</sub> | <sub>12.5569</sub> <sub>ms</sub> | <sub>11.9072</sub> <sub>ms</sub> | <sub>12.1086</sub> <sub>ms</sub> | <sub>11.7493</sub> <sub>ms</sub> |
| <sub>800000</sub> | <sub>13.8100</sub> <sub>ms</sub> | <sub>14.9648</sub> <sub>ms</sub> | <sub>14.9357</sub> <sub>ms</sub> | <sub>14.7252</sub> <sub>ms</sub> | <sub>14.2899</sub> <sub>ms</sub> |
| <sub>900000</sub> | <sub>17.8260</sub> <sub>ms</sub> | <sub>17.9126</sub> <sub>ms</sub> | <sub>17.8071</sub> <sub>ms</sub> | <sub>17.6653</sub> <sub>ms</sub> | <sub>16.5598</sub> <sub>ms</sub> |
| <sub>1000000</sub> | <sub>18.7424</sub> <sub>ms</sub> | <sub>20.6326</sub> <sub>ms</sub> | <sub>20.6248</sub> <sub>ms</sub> | <sub>20.3646</sub> <sub>ms</sub> | <sub>18.6638</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_random_large</sub>

| <sub>counts</sub> | <sub>std::vector</sub> | <sub>eastl::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> | <sub>carray</sub> |
|--------:|-------------|---------------|---------------|------------|------------|
| <sub>100000</sub> | <sub>2.8695</sub> <sub>ms</sub> | <sub>1.9055</sub> <sub>ms</sub> | <sub>2.0528</sub> <sub>ms</sub> | <sub>1.9727</sub> <sub>ms</sub> | <sub>2.4154</sub> <sub>ms</sub> |
| <sub>200000</sub> | <sub>4.6309</sub> <sub>ms</sub> | <sub>4.4411</sub> <sub>ms</sub> | <sub>4.7103</sub> <sub>ms</sub> | <sub>4.5928</sub> <sub>ms</sub> | <sub>4.8088</sub> <sub>ms</sub> |
| <sub>300000</sub> | <sub>7.8132</sub> <sub>ms</sub> | <sub>7.1768</sub> <sub>ms</sub> | <sub>7.8538</sub> <sub>ms</sub> | <sub>7.7742</sub> <sub>ms</sub> | <sub>7.7942</sub> <sub>ms</sub> |
| <sub>400000</sub> | <sub>12.3929</sub> <sub>ms</sub> | <sub>12.4093</sub> <sub>ms</sub> | <sub>12.3329</sub> <sub>ms</sub> | <sub>12.5360</sub> <sub>ms</sub> | <sub>13.4506</sub> <sub>ms</sub> |
| <sub>500000</sub> | <sub>17.7810</sub> <sub>ms</sub> | <sub>18.1099</sub> <sub>ms</sub> | <sub>17.3735</sub> <sub>ms</sub> | <sub>17.8010</sub> <sub>ms</sub> | <sub>16.7615</sub> <sub>ms</sub> |
| <sub>600000</sub> | <sub>22.7329</sub> <sub>ms</sub> | <sub>23.0500</sub> <sub>ms</sub> | <sub>22.4068</sub> <sub>ms</sub> | <sub>22.7911</sub> <sub>ms</sub> | <sub>22.7921</sub> <sub>ms</sub> |
| <sub>700000</sub> | <sub>24.2275</sub> <sub>ms</sub> | <sub>27.7321</sub> <sub>ms</sub> | <sub>27.0947</sub> <sub>ms</sub> | <sub>27.8435</sub> <sub>ms</sub> | <sub>27.0367</sub> <sub>ms</sub> |
| <sub>800000</sub> | <sub>32.2001</sub> <sub>ms</sub> | <sub>32.2912</sub> <sub>ms</sub> | <sub>32.3264</sub> <sub>ms</sub> | <sub>31.5190</sub> <sub>ms</sub> | <sub>30.4063</sub> <sub>ms</sub> |
| <sub>900000</sub> | <sub>35.7571</sub> <sub>ms</sub> | <sub>36.4017</sub> <sub>ms</sub> | <sub>36.3096</sub> <sub>ms</sub> | <sub>35.9511</sub> <sub>ms</sub> | <sub>36.0292</sub> <sub>ms</sub> |
| <sub>1000000</sub> | <sub>36.8750</sub> <sub>ms</sub> | <sub>40.2151</sub> <sub>ms</sub> | <sub>40.4876</sub> <sub>ms</sub> | <sub>40.6841</sub> <sub>ms</sub> | <sub>38.4951</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>sum</sub>

| <sub>counts</sub> | <sub>std::vector</sub> | <sub>eastl::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> | <sub>carray</sub> |
|--------:|-------------|---------------|---------------|-----------|-----------|
| <sub>100000</sub> | <sub>0.0354</sub> <sub>ms</sub> | <sub>0.0260</sub> <sub>ms</sub> | <sub>0.0295</sub> <sub>ms</sub> | <sub>0.0270</sub> <sub>ms</sub> | <sub>0.0380</sub> <sub>ms</sub> |
| <sub>200000</sub> | <sub>0.0632</sub> <sub>ms</sub> | <sub>0.0619</sub> <sub>ms</sub> | <sub>0.0630</sub> <sub>ms</sub> | <sub>0.0615</sub> <sub>ms</sub> | <sub>0.0755</sub> <sub>ms</sub> |
| <sub>300000</sub> | <sub>0.1009</sub> <sub>ms</sub> | <sub>0.1003</sub> <sub>ms</sub> | <sub>0.1005</sub> <sub>ms</sub> | <sub>0.1016</sub> <sub>ms</sub> | <sub>0.1243</sub> <sub>ms</sub> |
| <sub>400000</sub> | <sub>0.1418</sub> <sub>ms</sub> | <sub>0.1431</sub> <sub>ms</sub> | <sub>0.1459</sub> <sub>ms</sub> | <sub>0.1439</sub> <sub>ms</sub> | <sub>0.1750</sub> <sub>ms</sub> |
| <sub>500000</sub> | <sub>0.1847</sub> <sub>ms</sub> | <sub>0.1895</sub> <sub>ms</sub> | <sub>0.1838</sub> <sub>ms</sub> | <sub>0.1847</sub> <sub>ms</sub> | <sub>0.2453</sub> <sub>ms</sub> |
| <sub>600000</sub> | <sub>0.2327</sub> <sub>ms</sub> | <sub>0.2318</sub> <sub>ms</sub> | <sub>0.2320</sub> <sub>ms</sub> | <sub>0.2331</sub> <sub>ms</sub> | <sub>0.2864</sub> <sub>ms</sub> |
| <sub>700000</sub> | <sub>0.3028</sub> <sub>ms</sub> | <sub>0.2751</sub> <sub>ms</sub> | <sub>0.2731</sub> <sub>ms</sub> | <sub>0.2757</sub> <sub>ms</sub> | <sub>0.3479</sub> <sub>ms</sub> |
| <sub>800000</sub> | <sub>0.3164</sub> <sub>ms</sub> | <sub>0.3124</sub> <sub>ms</sub> | <sub>0.3092</sub> <sub>ms</sub> | <sub>0.3097</sub> <sub>ms</sub> | <sub>0.3748</sub> <sub>ms</sub> |
| <sub>900000</sub> | <sub>0.3484</sub> <sub>ms</sub> | <sub>0.3535</sub> <sub>ms</sub> | <sub>0.3490</sub> <sub>ms</sub> | <sub>0.3512</sub> <sub>ms</sub> | <sub>0.4793</sub> <sub>ms</sub> |
| <sub>1000000</sub> | <sub>0.3866</sub> <sub>ms</sub> | <sub>0.3863</sub> <sub>ms</sub> | <sub>0.3886</sub> <sub>ms</sub> | <sub>0.3884</sub> <sub>ms</sub> | <sub>0.5242</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>push_back</sub>

| <sub>counts</sub> | <sub>std::vector</sub> | <sub>eastl::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> | <sub>carray</sub> |
|--------:|-------------|---------------|---------------|-----------|-----------|
| <sub>100000</sub> | <sub>0.1538</sub> <sub>ms</sub> | <sub>0.0752</sub> <sub>ms</sub> | <sub>0.1444</sub> <sub>ms</sub> | <sub>0.0405</sub> <sub>ms</sub> | <sub>0.0342</sub> <sub>ms</sub> |
| <sub>200000</sub> | <sub>0.2766</sub> <sub>ms</sub> | <sub>0.1671</sub> <sub>ms</sub> | <sub>0.2606</sub> <sub>ms</sub> | <sub>0.0877</sub> <sub>ms</sub> | <sub>0.1000</sub> <sub>ms</sub> |
| <sub>300000</sub> | <sub>0.4150</sub> <sub>ms</sub> | <sub>0.2257</sub> <sub>ms</sub> | <sub>0.3908</sub> <sub>ms</sub> | <sub>0.1219</sub> <sub>ms</sub> | <sub>0.1267</sub> <sub>ms</sub> |
| <sub>400000</sub> | <sub>0.5536</sub> <sub>ms</sub> | <sub>0.3010</sub> <sub>ms</sub> | <sub>0.5652</sub> <sub>ms</sub> | <sub>0.1645</sub> <sub>ms</sub> | <sub>0.1822</sub> <sub>ms</sub> |
| <sub>500000</sub> | <sub>0.6933</sub> <sub>ms</sub> | <sub>0.3772</sub> <sub>ms</sub> | <sub>0.6537</sub> <sub>ms</sub> | <sub>0.2218</sub> <sub>ms</sub> | <sub>0.2511</sub> <sub>ms</sub> |
| <sub>600000</sub> | <sub>0.8327</sub> <sub>ms</sub> | <sub>0.5024</sub> <sub>ms</sub> | <sub>0.8588</sub> <sub>ms</sub> | <sub>0.2611</sub> <sub>ms</sub> | <sub>0.3052</sub> <sub>ms</sub> |
| <sub>700000</sub> | <sub>0.9690</sub> <sub>ms</sub> | <sub>0.5647</sub> <sub>ms</sub> | <sub>0.9205</sub> <sub>ms</sub> | <sub>0.3401</sub> <sub>ms</sub> | <sub>0.3498</sub> <sub>ms</sub> |
| <sub>800000</sub> | <sub>1.2133</sub> <sub>ms</sub> | <sub>0.6733</sub> <sub>ms</sub> | <sub>1.0508</sub> <sub>ms</sub> | <sub>0.4059</sub> <sub>ms</sub> | <sub>0.4152</sub> <sub>ms</sub> |
| <sub>900000</sub> | <sub>1.2480</sub> <sub>ms</sub> | <sub>0.7064</sub> <sub>ms</sub> | <sub>1.1754</sub> <sub>ms</sub> | <sub>0.4026</sub> <sub>ms</sub> | <sub>0.4551</sub> <sub>ms</sub> |
| <sub>1000000</sub> | <sub>1.3864</sub> <sub>ms</sub> | <sub>0.7664</sub> <sub>ms</sub> | <sub>1.3061</sub> <sub>ms</sub> | <sub>0.4482</sub> <sub>ms</sub> | <sub>0.5036</sub> <sub>ms</sub> |


