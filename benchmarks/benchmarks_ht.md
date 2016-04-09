# Hashtable benchmarks

Benchmarks run on a: MacBookPro10,2   Intel(R) Core(TM) i7-3520M CPU @ 2.90GHz

# Images
<img src="../images/timings_insert_sequential.png" alt="Timings insert_sequential" width="350">
<img src="../images/timings_insert_random.png" alt="Timings insert_random" width="350">
<img src="../images/timings_get_sequential.png" alt="Timings get_sequential" width="350">
<img src="../images/timings_get_random.png" alt="Timings get_random" width="350">
<img src="../images/timings_erase_sequential.png" alt="Timings erase_sequential" width="350">
<img src="../images/timings_erase_random.png" alt="Timings erase_random" width="350">
<img src="../images/timings_iterator.png" alt="Timings iterator" width="350">
<img src="../images/timings_create_insert_sum.png" alt="Timings create_insert_sum" width="350">
<img src="../images/timings_adds_and_removes.png" alt="Timings adds_and_removes" width="350">
# Tables
<sub>
## <sub>Timings</sub> <sub>insert_sequential</sub>

| <sub>counts</sub> | <sub>std::map</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|------------|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0802</sub> <sub>ms</sub> | <sub>0.0725</sub> <sub>ms</sub> | <sub>0.0691</sub> <sub>ms</sub> | <sub>0.0554</sub> <sub>ms</sub> | <sub>0.0240</sub> <sub>ms</sub> | <sub>0.0028</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4258</sub> <sub>ms</sub> | <sub>0.3602</sub> <sub>ms</sub> | <sub>0.3419</sub> <sub>ms</sub> | <sub>0.2779</sub> <sub>ms</sub> | <sub>0.1362</sub> <sub>ms</sub> | <sub>0.0112</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.9642</sub> <sub>ms</sub> | <sub>0.7154</sub> <sub>ms</sub> | <sub>0.6834</sub> <sub>ms</sub> | <sub>0.5384</sub> <sub>ms</sub> | <sub>0.2709</sub> <sub>ms</sub> | <sub>0.0224</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.3658</sub> <sub>ms</sub> | <sub>1.4269</sub> <sub>ms</sub> | <sub>1.3671</sub> <sub>ms</sub> | <sub>1.1200</sub> <sub>ms</sub> | <sub>0.5878</sub> <sub>ms</sub> | <sub>0.0448</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>3.8692</sub> <sub>ms</sub> | <sub>2.1779</sub> <sub>ms</sub> | <sub>2.0989</sub> <sub>ms</sub> | <sub>1.6287</sub> <sub>ms</sub> | <sub>0.6823</sub> <sub>ms</sub> | <sub>0.0672</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.2461</sub> <sub>ms</sub> | <sub>2.9335</sub> <sub>ms</sub> | <sub>2.7702</sub> <sub>ms</sub> | <sub>2.2794</sub> <sub>ms</sub> | <sub>1.2308</sub> <sub>ms</sub> | <sub>0.0896</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>6.5149</sub> <sub>ms</sub> | <sub>3.6961</sub> <sub>ms</sub> | <sub>3.5981</sub> <sub>ms</sub> | <sub>2.8482</sub> <sub>ms</sub> | <sub>1.3850</sub> <sub>ms</sub> | <sub>0.1118</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>8.1726</sub> <sub>ms</sub> | <sub>4.4058</sub> <sub>ms</sub> | <sub>4.2694</sub> <sub>ms</sub> | <sub>3.3582</sub> <sub>ms</sub> | <sub>1.5424</sub> <sub>ms</sub> | <sub>0.1347</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>9.5657</sub> <sub>ms</sub> | <sub>5.2059</sub> <sub>ms</sub> | <sub>5.0046</sub> <sub>ms</sub> | <sub>4.0261</sub> <sub>ms</sub> | <sub>2.7523</sub> <sub>ms</sub> | <sub>0.1567</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>11.4113</sub> <sub>ms</sub> | <sub>6.0114</sub> <sub>ms</sub> | <sub>5.6983</sub> <sub>ms</sub> | <sub>5.0212</sub> <sub>ms</sub> | <sub>3.0386</sub> <sub>ms</sub> | <sub>0.1791</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>12.8696</sub> <sub>ms</sub> | <sub>6.7499</sub> <sub>ms</sub> | <sub>6.4219</sub> <sub>ms</sub> | <sub>5.1815</sub> <sub>ms</sub> | <sub>3.1889</sub> <sub>ms</sub> | <sub>0.2018</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>13.4134</sub> <sub>ms</sub> | <sub>7.9089</sub> <sub>ms</sub> | <sub>7.5581</sub> <sub>ms</sub> | <sub>5.9316</sub> <sub>ms</sub> | <sub>3.1635</sub> <sub>ms</sub> | <sub>0.2242</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>insert_random</sub>

| <sub>counts</sub> | <sub>std::map</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|------------|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1073</sub> <sub>ms</sub> | <sub>0.0853</sub> <sub>ms</sub> | <sub>0.0770</sub> <sub>ms</sub> | <sub>0.0623</sub> <sub>ms</sub> | <sub>0.0337</sub> <sub>ms</sub> | <sub>0.0065</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.6459</sub> <sub>ms</sub> | <sub>0.4472</sub> <sub>ms</sub> | <sub>0.3969</sub> <sub>ms</sub> | <sub>0.3170</sub> <sub>ms</sub> | <sub>0.2351</sub> <sub>ms</sub> | <sub>0.0605</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.4282</sub> <sub>ms</sub> | <sub>0.9095</sub> <sub>ms</sub> | <sub>0.8194</sub> <sub>ms</sub> | <sub>0.6378</sub> <sub>ms</sub> | <sub>0.4798</sub> <sub>ms</sub> | <sub>0.1271</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>3.1872</sub> <sub>ms</sub> | <sub>1.8859</sub> <sub>ms</sub> | <sub>1.6903</sub> <sub>ms</sub> | <sub>1.3735</sub> <sub>ms</sub> | <sub>0.9772</sub> <sub>ms</sub> | <sub>0.2768</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>5.2263</sub> <sub>ms</sub> | <sub>2.8771</sub> <sub>ms</sub> | <sub>2.5930</sub> <sub>ms</sub> | <sub>2.1931</sub> <sub>ms</sub> | <sub>1.2346</sub> <sub>ms</sub> | <sub>0.3219</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>7.8693</sub> <sub>ms</sub> | <sub>4.1313</sub> <sub>ms</sub> | <sub>3.6080</sub> <sub>ms</sub> | <sub>3.2183</sub> <sub>ms</sub> | <sub>2.1615</sub> <sub>ms</sub> | <sub>0.5854</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>10.2801</sub> <sub>ms</sub> | <sub>5.5513</sub> <sub>ms</sub> | <sub>4.3400</sub> <sub>ms</sub> | <sub>3.9166</sub> <sub>ms</sub> | <sub>2.4408</sub> <sub>ms</sub> | <sub>1.0116</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>12.0523</sub> <sub>ms</sub> | <sub>6.7824</sub> <sub>ms</sub> | <sub>5.3988</sub> <sub>ms</sub> | <sub>4.8589</sub> <sub>ms</sub> | <sub>2.8044</sub> <sub>ms</sub> | <sub>0.6870</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>16.5229</sub> <sub>ms</sub> | <sub>8.3509</sub> <sub>ms</sub> | <sub>6.6463</sub> <sub>ms</sub> | <sub>6.3820</sub> <sub>ms</sub> | <sub>4.8736</sub> <sub>ms</sub> | <sub>0.9140</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>17.5495</sub> <sub>ms</sub> | <sub>9.1927</sub> <sub>ms</sub> | <sub>7.7960</sub> <sub>ms</sub> | <sub>7.7430</sub> <sub>ms</sub> | <sub>5.1202</sub> <sub>ms</sub> | <sub>1.2110</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>22.3379</sub> <sub>ms</sub> | <sub>10.9646</sub> <sub>ms</sub> | <sub>9.0820</sub> <sub>ms</sub> | <sub>8.5420</sub> <sub>ms</sub> | <sub>6.0926</sub> <sub>ms</sub> | <sub>1.6460</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>27.5763</sub> <sub>ms</sub> | <sub>14.3785</sub> <sub>ms</sub> | <sub>11.6984</sub> <sub>ms</sub> | <sub>10.0405</sub> <sub>ms</sub> | <sub>7.2054</sub> <sub>ms</sub> | <sub>2.1542</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_sequential</sub>

| <sub>counts</sub> | <sub>std::map</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|-----------|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0323</sub> <sub>ms</sub> | <sub>0.0214</sub> <sub>ms</sub> | <sub>0.0127</sub> <sub>ms</sub> | <sub>0.0112</sub> <sub>ms</sub> | <sub>0.0083</sub> <sub>ms</sub> | <sub>0.0015</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.2085</sub> <sub>ms</sub> | <sub>0.0871</sub> <sub>ms</sub> | <sub>0.0631</sub> <sub>ms</sub> | <sub>0.0564</sub> <sub>ms</sub> | <sub>0.0636</sub> <sub>ms</sub> | <sub>0.0061</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.3953</sub> <sub>ms</sub> | <sub>0.1751</sub> <sub>ms</sub> | <sub>0.1259</sub> <sub>ms</sub> | <sub>0.1130</sub> <sub>ms</sub> | <sub>0.0810</sub> <sub>ms</sub> | <sub>0.0124</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.8248</sub> <sub>ms</sub> | <sub>0.3525</sub> <sub>ms</sub> | <sub>0.2536</sub> <sub>ms</sub> | <sub>0.2251</sub> <sub>ms</sub> | <sub>0.1671</sub> <sub>ms</sub> | <sub>0.0312</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>1.2751</sub> <sub>ms</sub> | <sub>0.5192</sub> <sub>ms</sub> | <sub>0.4029</sub> <sub>ms</sub> | <sub>0.3398</sub> <sub>ms</sub> | <sub>0.2506</sub> <sub>ms</sub> | <sub>0.0373</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>1.8561</sub> <sub>ms</sub> | <sub>0.6988</sub> <sub>ms</sub> | <sub>0.4972</sub> <sub>ms</sub> | <sub>0.4505</sub> <sub>ms</sub> | <sub>0.3346</sub> <sub>ms</sub> | <sub>0.0495</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>2.2344</sub> <sub>ms</sub> | <sub>0.8808</sub> <sub>ms</sub> | <sub>0.6345</sub> <sub>ms</sub> | <sub>0.5669</sub> <sub>ms</sub> | <sub>0.4182</sub> <sub>ms</sub> | <sub>0.0765</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>2.9878</sub> <sub>ms</sub> | <sub>1.0552</sub> <sub>ms</sub> | <sub>0.7617</sub> <sub>ms</sub> | <sub>0.6864</sub> <sub>ms</sub> | <sub>0.4974</sub> <sub>ms</sub> | <sub>0.0742</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>3.3442</sub> <sub>ms</sub> | <sub>1.2269</sub> <sub>ms</sub> | <sub>0.8899</sub> <sub>ms</sub> | <sub>0.7952</sub> <sub>ms</sub> | <sub>0.5869</sub> <sub>ms</sub> | <sub>0.0867</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>3.9225</sub> <sub>ms</sub> | <sub>1.4087</sub> <sub>ms</sub> | <sub>1.0217</sub> <sub>ms</sub> | <sub>0.9230</sub> <sub>ms</sub> | <sub>0.6480</sub> <sub>ms</sub> | <sub>0.0994</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>4.4290</sub> <sub>ms</sub> | <sub>1.5867</sub> <sub>ms</sub> | <sub>1.1506</sub> <sub>ms</sub> | <sub>1.0384</sub> <sub>ms</sub> | <sub>0.7883</sub> <sub>ms</sub> | <sub>0.1131</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>5.2623</sub> <sub>ms</sub> | <sub>1.8398</sub> <sub>ms</sub> | <sub>1.2809</sub> <sub>ms</sub> | <sub>1.2003</sub> <sub>ms</sub> | <sub>0.8396</sub> <sub>ms</sub> | <sub>0.1317</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_random</sub>

| <sub>counts</sub> | <sub>std::map</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|------------|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0492</sub> <sub>ms</sub> | <sub>0.0295</sub> <sub>ms</sub> | <sub>0.0194</sub> <sub>ms</sub> | <sub>0.0166</sub> <sub>ms</sub> | <sub>0.0119</sub> <sub>ms</sub> | <sub>0.0068</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.3374</sub> <sub>ms</sub> | <sub>0.1361</sub> <sub>ms</sub> | <sub>0.1164</sub> <sub>ms</sub> | <sub>0.0881</sub> <sub>ms</sub> | <sub>0.0650</sub> <sub>ms</sub> | <sub>0.0417</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.8408</sub> <sub>ms</sub> | <sub>0.3122</sub> <sub>ms</sub> | <sub>0.2637</sub> <sub>ms</sub> | <sub>0.1965</sub> <sub>ms</sub> | <sub>0.1090</sub> <sub>ms</sub> | <sub>0.0855</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.0404</sub> <sub>ms</sub> | <sub>0.6809</sub> <sub>ms</sub> | <sub>0.7154</sub> <sub>ms</sub> | <sub>0.4161</sub> <sub>ms</sub> | <sub>0.2242</sub> <sub>ms</sub> | <sub>0.1865</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>3.4944</sub> <sub>ms</sub> | <sub>0.9794</sub> <sub>ms</sub> | <sub>1.1968</sub> <sub>ms</sub> | <sub>0.7414</sub> <sub>ms</sub> | <sub>0.4089</sub> <sub>ms</sub> | <sub>0.1854</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>4.8786</sub> <sub>ms</sub> | <sub>1.4308</sub> <sub>ms</sub> | <sub>1.1993</sub> <sub>ms</sub> | <sub>0.9075</sub> <sub>ms</sub> | <sub>0.5580</sub> <sub>ms</sub> | <sub>0.3903</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>6.6268</sub> <sub>ms</sub> | <sub>1.9312</sub> <sub>ms</sub> | <sub>1.9079</sub> <sub>ms</sub> | <sub>1.2086</sub> <sub>ms</sub> | <sub>0.7999</sub> <sub>ms</sub> | <sub>0.7357</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>10.1931</sub> <sub>ms</sub> | <sub>2.3144</sub> <sub>ms</sub> | <sub>1.9836</sub> <sub>ms</sub> | <sub>1.8509</sub> <sub>ms</sub> | <sub>0.9393</sub> <sub>ms</sub> | <sub>0.3950</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>11.9803</sub> <sub>ms</sub> | <sub>3.7506</sub> <sub>ms</sub> | <sub>2.7302</sub> <sub>ms</sub> | <sub>2.5889</sub> <sub>ms</sub> | <sub>2.2786</sub> <sub>ms</sub> | <sub>0.7024</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>15.2888</sub> <sub>ms</sub> | <sub>4.2790</sub> <sub>ms</sub> | <sub>3.5255</sub> <sub>ms</sub> | <sub>3.6485</sub> <sub>ms</sub> | <sub>2.0166</sub> <sub>ms</sub> | <sub>0.8231</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>18.5509</sub> <sub>ms</sub> | <sub>5.5539</sub> <sub>ms</sub> | <sub>4.9869</sub> <sub>ms</sub> | <sub>4.2034</sub> <sub>ms</sub> | <sub>2.6062</sub> <sub>ms</sub> | <sub>1.2738</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>25.9249</sub> <sub>ms</sub> | <sub>9.1423</sub> <sub>ms</sub> | <sub>7.4140</sub> <sub>ms</sub> | <sub>6.1423</sub> <sub>ms</sub> | <sub>2.7957</sub> <sub>ms</sub> | <sub>1.6640</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_sequential</sub>

| <sub>counts</sub> | <sub>std::map</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|------------|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1325</sub> <sub>ms</sub> | <sub>0.1396</sub> <sub>ms</sub> | <sub>0.0943</sub> <sub>ms</sub> | <sub>0.0892</sub> <sub>ms</sub> | <sub>0.0128</sub> <sub>ms</sub> | <sub>0.0102</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.7712</sub> <sub>ms</sub> | <sub>0.5743</sub> <sub>ms</sub> | <sub>0.4796</sub> <sub>ms</sub> | <sub>0.3643</sub> <sub>ms</sub> | <sub>0.0633</sub> <sub>ms</sub> | <sub>0.0746</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.6943</sub> <sub>ms</sub> | <sub>1.1755</sub> <sub>ms</sub> | <sub>0.9930</sub> <sub>ms</sub> | <sub>0.7503</sub> <sub>ms</sub> | <sub>0.1201</sub> <sub>ms</sub> | <sub>0.1572</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>3.8312</sub> <sub>ms</sub> | <sub>2.4067</sub> <sub>ms</sub> | <sub>2.2460</sub> <sub>ms</sub> | <sub>1.5221</sub> <sub>ms</sub> | <sub>0.2457</sub> <sub>ms</sub> | <sub>0.3431</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>6.5908</sub> <sub>ms</sub> | <sub>3.6517</sub> <sub>ms</sub> | <sub>3.7667</sub> <sub>ms</sub> | <sub>2.4438</sub> <sub>ms</sub> | <sub>0.4473</sub> <sub>ms</sub> | <sub>0.4746</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>9.8052</sub> <sub>ms</sub> | <sub>5.3849</sub> <sub>ms</sub> | <sub>4.2558</sub> <sub>ms</sub> | <sub>3.6027</sub> <sub>ms</sub> | <sub>0.6042</sub> <sub>ms</sub> | <sub>0.7185</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>12.7382</sub> <sub>ms</sub> | <sub>7.3999</sub> <sub>ms</sub> | <sub>5.3409</sub> <sub>ms</sub> | <sub>5.2301</sub> <sub>ms</sub> | <sub>0.8232</sub> <sub>ms</sub> | <sub>1.0964</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>16.2664</sub> <sub>ms</sub> | <sub>9.3226</sub> <sub>ms</sub> | <sub>7.9184</sub> <sub>ms</sub> | <sub>6.6272</sub> <sub>ms</sub> | <sub>1.0384</sub> <sub>ms</sub> | <sub>0.9303</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>20.4126</sub> <sub>ms</sub> | <sub>10.7017</sub> <sub>ms</sub> | <sub>8.5656</sub> <sub>ms</sub> | <sub>7.4440</sub> <sub>ms</sub> | <sub>2.7025</sub> <sub>ms</sub> | <sub>1.2143</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>23.0912</sub> <sub>ms</sub> | <sub>12.8798</sub> <sub>ms</sub> | <sub>10.9075</sub> <sub>ms</sub> | <sub>8.4963</sub> <sub>ms</sub> | <sub>2.5170</sub> <sub>ms</sub> | <sub>1.5707</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>30.0007</sub> <sub>ms</sub> | <sub>15.0499</sub> <sub>ms</sub> | <sub>12.5454</sub> <sub>ms</sub> | <sub>10.7494</sub> <sub>ms</sub> | <sub>3.1622</sub> <sub>ms</sub> | <sub>2.3072</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>36.5794</sub> <sub>ms</sub> | <sub>19.6268</sub> <sub>ms</sub> | <sub>17.4357</sub> <sub>ms</sub> | <sub>14.0138</sub> <sub>ms</sub> | <sub>3.6050</sub> <sub>ms</sub> | <sub>2.8170</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_random</sub>

| <sub>counts</sub> | <sub>std::map</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|------------|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1415</sub> <sub>ms</sub> | <sub>0.1340</sub> <sub>ms</sub> | <sub>0.1035</sub> <sub>ms</sub> | <sub>0.1023</sub> <sub>ms</sub> | <sub>0.0133</sub> <sub>ms</sub> | <sub>0.0193</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.8225</sub> <sub>ms</sub> | <sub>0.6186</sub> <sub>ms</sub> | <sub>0.5265</sub> <sub>ms</sub> | <sub>0.4092</sub> <sub>ms</sub> | <sub>0.0573</sub> <sub>ms</sub> | <sub>0.0921</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.9088</sub> <sub>ms</sub> | <sub>1.3332</sub> <sub>ms</sub> | <sub>1.1226</sub> <sub>ms</sub> | <sub>0.8561</sub> <sub>ms</sub> | <sub>0.1197</sub> <sub>ms</sub> | <sub>0.1685</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>4.2745</sub> <sub>ms</sub> | <sub>2.7131</sub> <sub>ms</sub> | <sub>2.3717</sub> <sub>ms</sub> | <sub>1.7915</sub> <sub>ms</sub> | <sub>0.2446</sub> <sub>ms</sub> | <sub>0.3328</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>7.2227</sub> <sub>ms</sub> | <sub>4.2025</sub> <sub>ms</sub> | <sub>3.6643</sub> <sub>ms</sub> | <sub>2.8093</sub> <sub>ms</sub> | <sub>0.4428</sub> <sub>ms</sub> | <sub>0.4497</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>10.6729</sub> <sub>ms</sub> | <sub>6.6801</sub> <sub>ms</sub> | <sub>4.8988</sub> <sub>ms</sub> | <sub>4.1377</sub> <sub>ms</sub> | <sub>0.5954</sub> <sub>ms</sub> | <sub>0.6920</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>14.6532</sub> <sub>ms</sub> | <sub>7.9074</sub> <sub>ms</sub> | <sub>7.9514</sub> <sub>ms</sub> | <sub>5.2504</sub> <sub>ms</sub> | <sub>0.7684</sub> <sub>ms</sub> | <sub>1.0717</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>20.0346</sub> <sub>ms</sub> | <sub>10.0052</sub> <sub>ms</sub> | <sub>8.9568</sub> <sub>ms</sub> | <sub>6.2528</sub> <sub>ms</sub> | <sub>1.0144</sub> <sub>ms</sub> | <sub>0.8986</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>26.5509</sub> <sub>ms</sub> | <sub>12.9176</sub> <sub>ms</sub> | <sub>12.2195</sub> <sub>ms</sub> | <sub>9.4370</sub> <sub>ms</sub> | <sub>2.2912</sub> <sub>ms</sub> | <sub>1.4892</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>29.6929</sub> <sub>ms</sub> | <sub>14.9231</sub> <sub>ms</sub> | <sub>13.0560</sub> <sub>ms</sub> | <sub>12.3380</sub> <sub>ms</sub> | <sub>2.3744</sub> <sub>ms</sub> | <sub>1.4469</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>35.2480</sub> <sub>ms</sub> | <sub>18.9232</sub> <sub>ms</sub> | <sub>18.6434</sub> <sub>ms</sub> | <sub>14.9923</sub> <sub>ms</sub> | <sub>3.2399</sub> <sub>ms</sub> | <sub>2.0224</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>48.7126</sub> <sub>ms</sub> | <sub>26.6677</sub> <sub>ms</sub> | <sub>25.6908</sub> <sub>ms</sub> | <sub>19.6872</sub> <sub>ms</sub> | <sub>3.4337</sub> <sub>ms</sub> | <sub>2.5271</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>iterator</sub>

| <sub>counts</sub> | <sub>std::map</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|-----------|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0070</sub> <sub>ms</sub> | <sub>0.0029</sub> <sub>ms</sub> | <sub>0.0027</sub> <sub>ms</sub> | <sub>0.0076</sub> <sub>ms</sub> | <sub>0.0076</sub> <sub>ms</sub> | <sub>0.0055</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0458</sub> <sub>ms</sub> | <sub>0.0196</sub> <sub>ms</sub> | <sub>0.0206</sub> <sub>ms</sub> | <sub>0.0416</sub> <sub>ms</sub> | <sub>0.0518</sub> <sub>ms</sub> | <sub>0.0255</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.1235</sub> <sub>ms</sub> | <sub>0.0501</sub> <sub>ms</sub> | <sub>0.0511</sub> <sub>ms</sub> | <sub>0.0884</sub> <sub>ms</sub> | <sub>0.1034</sub> <sub>ms</sub> | <sub>0.0507</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.2750</sub> <sub>ms</sub> | <sub>0.1361</sub> <sub>ms</sub> | <sub>0.1350</sub> <sub>ms</sub> | <sub>0.1844</sub> <sub>ms</sub> | <sub>0.2070</sub> <sub>ms</sub> | <sub>0.1085</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.4379</sub> <sub>ms</sub> | <sub>0.2264</sub> <sub>ms</sub> | <sub>0.2260</sub> <sub>ms</sub> | <sub>0.2466</sub> <sub>ms</sub> | <sub>0.2544</sub> <sub>ms</sub> | <sub>0.2437</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>0.6536</sub> <sub>ms</sub> | <sub>0.3023</sub> <sub>ms</sub> | <sub>0.2997</sub> <sub>ms</sub> | <sub>0.3819</sub> <sub>ms</sub> | <sub>0.4248</sub> <sub>ms</sub> | <sub>0.2154</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>0.9235</sub> <sub>ms</sub> | <sub>0.3913</sub> <sub>ms</sub> | <sub>0.4248</sub> <sub>ms</sub> | <sub>0.4623</sub> <sub>ms</sub> | <sub>0.4825</sub> <sub>ms</sub> | <sub>0.1684</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>1.8568</sub> <sub>ms</sub> | <sub>0.5533</sub> <sub>ms</sub> | <sub>0.5267</sub> <sub>ms</sub> | <sub>0.5474</sub> <sub>ms</sub> | <sub>0.5213</sub> <sub>ms</sub> | <sub>0.4679</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>2.3600</sub> <sub>ms</sub> | <sub>0.8922</sub> <sub>ms</sub> | <sub>0.8824</sub> <sub>ms</sub> | <sub>0.8541</sub> <sub>ms</sub> | <sub>0.8709</sub> <sub>ms</sub> | <sub>0.5124</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>2.7463</sub> <sub>ms</sub> | <sub>1.0714</sub> <sub>ms</sub> | <sub>1.1593</sub> <sub>ms</sub> | <sub>1.0115</sub> <sub>ms</sub> | <sub>0.9414</sub> <sub>ms</sub> | <sub>0.4316</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>3.6761</sub> <sub>ms</sub> | <sub>1.5040</sub> <sub>ms</sub> | <sub>1.5717</sub> <sub>ms</sub> | <sub>1.1598</sub> <sub>ms</sub> | <sub>1.0108</sub> <sub>ms</sub> | <sub>0.4188</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>5.8521</sub> <sub>ms</sub> | <sub>2.3041</sub> <sub>ms</sub> | <sub>2.8964</sub> <sub>ms</sub> | <sub>1.4298</sub> <sub>ms</sub> | <sub>1.0803</sub> <sub>ms</sub> | <sub>0.3429</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>create_insert_sum</sub>

| <sub>counts</sub> | <sub>std::map</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|------------|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1490</sub> <sub>ms</sub> | <sub>0.1432</sub> <sub>ms</sub> | <sub>0.1763</sub> <sub>ms</sub> | <sub>0.1435</sub> <sub>ms</sub> | <sub>0.0201</sub> <sub>ms</sub> | <sub>0.0230</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.7830</sub> <sub>ms</sub> | <sub>0.6947</sub> <sub>ms</sub> | <sub>0.7175</sub> <sub>ms</sub> | <sub>0.6330</sub> <sub>ms</sub> | <sub>0.1092</sub> <sub>ms</sub> | <sub>0.0639</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.7164</sub> <sub>ms</sub> | <sub>1.5098</sub> <sub>ms</sub> | <sub>1.3239</sub> <sub>ms</sub> | <sub>1.2730</sub> <sub>ms</sub> | <sub>0.2695</sub> <sub>ms</sub> | <sub>0.1288</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>3.6492</sub> <sub>ms</sub> | <sub>2.8043</sub> <sub>ms</sub> | <sub>2.6340</sub> <sub>ms</sub> | <sub>2.5545</sub> <sub>ms</sub> | <sub>0.4330</sub> <sub>ms</sub> | <sub>0.2948</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>6.0834</sub> <sub>ms</sub> | <sub>4.2661</sub> <sub>ms</sub> | <sub>4.2103</sub> <sub>ms</sub> | <sub>3.6886</sub> <sub>ms</sub> | <sub>0.5949</sub> <sub>ms</sub> | <sub>0.6459</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>8.5289</sub> <sub>ms</sub> | <sub>5.7223</sub> <sub>ms</sub> | <sub>5.4592</sub> <sub>ms</sub> | <sub>5.6890</sub> <sub>ms</sub> | <sub>0.8656</sub> <sub>ms</sub> | <sub>0.5315</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>11.1490</sub> <sub>ms</sub> | <sub>7.0736</sub> <sub>ms</sub> | <sub>7.3121</sub> <sub>ms</sub> | <sub>6.3317</sub> <sub>ms</sub> | <sub>1.0270</sub> <sub>ms</sub> | <sub>0.5614</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>13.5473</sub> <sub>ms</sub> | <sub>8.9647</sub> <sub>ms</sub> | <sub>8.4581</sub> <sub>ms</sub> | <sub>8.1964</sub> <sub>ms</sub> | <sub>1.1892</sub> <sub>ms</sub> | <sub>0.9881</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>16.0433</sub> <sub>ms</sub> | <sub>10.5416</sub> <sub>ms</sub> | <sub>9.8002</sub> <sub>ms</sub> | <sub>10.3466</sub> <sub>ms</sub> | <sub>1.6437</sub> <sub>ms</sub> | <sub>1.5676</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>19.7443</sub> <sub>ms</sub> | <sub>11.6952</sub> <sub>ms</sub> | <sub>11.2100</sub> <sub>ms</sub> | <sub>11.1506</sub> <sub>ms</sub> | <sub>1.8042</sub> <sub>ms</sub> | <sub>1.3084</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>22.4604</sub> <sub>ms</sub> | <sub>13.0518</sub> <sub>ms</sub> | <sub>12.5109</sub> <sub>ms</sub> | <sub>12.4837</sub> <sub>ms</sub> | <sub>2.0461</sub> <sub>ms</sub> | <sub>1.1504</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>23.9775</sub> <sub>ms</sub> | <sub>15.1889</sub> <sub>ms</sub> | <sub>15.6737</sub> <sub>ms</sub> | <sub>14.6995</sub> <sub>ms</sub> | <sub>2.2220</sub> <sub>ms</sub> | <sub>1.1425</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>adds_and_removes</sub>

| <sub>counts</sub> | <sub>std::map</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|-------------|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>1.1713</sub> <sub>ms</sub> | <sub>0.9456</sub> <sub>ms</sub> | <sub>0.9826</sub> <sub>ms</sub> | <sub>0.6992</sub> <sub>ms</sub> | <sub>0.4200</sub> <sub>ms</sub> | <sub>0.4148</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>6.1745</sub> <sub>ms</sub> | <sub>4.3015</sub> <sub>ms</sub> | <sub>3.8090</sub> <sub>ms</sub> | <sub>3.1138</sub> <sub>ms</sub> | <sub>2.1556</sub> <sub>ms</sub> | <sub>1.5921</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>14.8754</sub> <sub>ms</sub> | <sub>9.4371</sub> <sub>ms</sub> | <sub>8.4725</sub> <sub>ms</sub> | <sub>6.7312</sub> <sub>ms</sub> | <sub>4.4914</sub> <sub>ms</sub> | <sub>3.4028</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>39.9953</sub> <sub>ms</sub> | <sub>23.3505</sub> <sub>ms</sub> | <sub>21.3940</sub> <sub>ms</sub> | <sub>17.9572</sub> <sub>ms</sub> | <sub>11.0717</sub> <sub>ms</sub> | <sub>8.6558</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>61.8252</sub> <sub>ms</sub> | <sub>35.6864</sub> <sub>ms</sub> | <sub>32.5105</sub> <sub>ms</sub> | <sub>25.2157</sub> <sub>ms</sub> | <sub>14.1257</sub> <sub>ms</sub> | <sub>11.8649</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>105.2262</sub> <sub>ms</sub> | <sub>52.3959</sub> <sub>ms</sub> | <sub>47.5121</sub> <sub>ms</sub> | <sub>39.4516</sub> <sub>ms</sub> | <sub>24.4584</sub> <sub>ms</sub> | <sub>20.1923</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>149.9382</sub> <sub>ms</sub> | <sub>75.9952</sub> <sub>ms</sub> | <sub>69.1855</sub> <sub>ms</sub> | <sub>52.9549</sub> <sub>ms</sub> | <sub>32.5811</sub> <sub>ms</sub> | <sub>28.0107</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>195.9146</sub> <sub>ms</sub> | <sub>100.6947</sub> <sub>ms</sub> | <sub>88.9579</sub> <sub>ms</sub> | <sub>68.8032</sub> <sub>ms</sub> | <sub>36.6249</sub> <sub>ms</sub> | <sub>28.5445</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>237.0496</sub> <sub>ms</sub> | <sub>109.4840</sub> <sub>ms</sub> | <sub>109.6852</sub> <sub>ms</sub> | <sub>81.5113</sub> <sub>ms</sub> | <sub>45.4683</sub> <sub>ms</sub> | <sub>30.7278</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>305.6468</sub> <sub>ms</sub> | <sub>150.8465</sub> <sub>ms</sub> | <sub>146.8488</sub> <sub>ms</sub> | <sub>108.2369</sub> <sub>ms</sub> | <sub>69.6179</sub> <sub>ms</sub> | <sub>42.1046</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>314.1027</sub> <sub>ms</sub> | <sub>167.0097</sub> <sub>ms</sub> | <sub>164.7762</sub> <sub>ms</sub> | <sub>120.9485</sub> <sub>ms</sub> | <sub>81.4235</sub> <sub>ms</sub> | <sub>47.0265</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>465.3704</sub> <sub>ms</sub> | <sub>253.8640</sub> <sub>ms</sub> | <sub>245.5511</sub> <sub>ms</sub> | <sub>167.9563</sub> <sub>ms</sub> | <sub>98.5670</sub> <sub>ms</sub> | <sub>65.4415</sub> <sub>ms</sub> |


