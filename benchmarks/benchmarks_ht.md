# Hashtable benchmarks

Benchmarks run on a: MacBookPro10,2   Intel(R) Core(TM) i7-3520M CPU @ 2.90GHz

# Images
<img src="../images/timings_insert_sequential_sizeof(value)==8.png" alt="Timings insert_sequential sizeof(value)==8" width="350">
<img src="../images/timings_insert_sequential_sizeof(value)==152.png" alt="Timings insert_sequential sizeof(value)==152" width="350">
<br/>
<img src="../images/timings_insert_random_sizeof(value)==8.png" alt="Timings insert_random sizeof(value)==8" width="350">
<img src="../images/timings_insert_random_sizeof(value)==152.png" alt="Timings insert_random sizeof(value)==152" width="350">
<br/>
<img src="../images/timings_get_sequential_sizeof(value)==8.png" alt="Timings get_sequential sizeof(value)==8" width="350">
<img src="../images/timings_get_sequential_sizeof(value)==152.png" alt="Timings get_sequential sizeof(value)==152" width="350">
<br/>
<img src="../images/timings_get_random_sizeof(value)==8.png" alt="Timings get_random sizeof(value)==8" width="350">
<img src="../images/timings_get_random_sizeof(value)==152.png" alt="Timings get_random sizeof(value)==152" width="350">
<br/>
<img src="../images/timings_erase_sequential_sizeof(value)==8.png" alt="Timings erase_sequential sizeof(value)==8" width="350">
<img src="../images/timings_erase_sequential_sizeof(value)==152.png" alt="Timings erase_sequential sizeof(value)==152" width="350">
<br/>
<img src="../images/timings_erase_random_sizeof(value)==8.png" alt="Timings erase_random sizeof(value)==8" width="350">
<img src="../images/timings_erase_random_sizeof(value)==152.png" alt="Timings erase_random sizeof(value)==152" width="350">
<br/>
<img src="../images/timings_iterator_sizeof(value)==8.png" alt="Timings iterator sizeof(value)==8" width="350">
<img src="../images/timings_iterator_sizeof(value)==152.png" alt="Timings iterator sizeof(value)==152" width="350">
<br/>
<img src="../images/timings_create_insert_sum_sizeof(value)==8.png" alt="Timings create_insert_sum sizeof(value)==8" width="350">
<img src="../images/timings_create_insert_sum_sizeof(value)==152.png" alt="Timings create_insert_sum sizeof(value)==152" width="350">
<br/>
<img src="../images/timings_adds_and_removes_sizeof(value)==8.png" alt="Timings adds_and_removes sizeof(value)==8" width="350">
<img src="../images/timings_adds_and_removes_sizeof(value)==152.png" alt="Timings adds_and_removes sizeof(value)==152" width="350">
<br/>
# Tables

### log_new_small_2.txt
<sub>
## <sub>Timings</sub> <sub>insert_sequential</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0728</sub> <sub>ms</sub> | <sub>0.0546</sub> <sub>ms</sub> | <sub>0.0399</sub> <sub>ms</sub> | <sub>0.0034</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.3616</sub> <sub>ms</sub> | <sub>0.2897</sub> <sub>ms</sub> | <sub>0.1470</sub> <sub>ms</sub> | <sub>0.0175</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.7241</sub> <sub>ms</sub> | <sub>0.5366</sub> <sub>ms</sub> | <sub>0.3004</sub> <sub>ms</sub> | <sub>0.0366</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>1.5240</sub> <sub>ms</sub> | <sub>1.0663</sub> <sub>ms</sub> | <sub>0.5473</sub> <sub>ms</sub> | <sub>0.0695</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>2.1727</sub> <sub>ms</sub> | <sub>1.6389</sub> <sub>ms</sub> | <sub>0.6967</sub> <sub>ms</sub> | <sub>0.1049</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>2.9295</sub> <sub>ms</sub> | <sub>2.2227</sub> <sub>ms</sub> | <sub>1.2207</sub> <sub>ms</sub> | <sub>0.1397</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>3.6769</sub> <sub>ms</sub> | <sub>2.7999</sub> <sub>ms</sub> | <sub>1.3894</sub> <sub>ms</sub> | <sub>0.1744</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>4.3963</sub> <sub>ms</sub> | <sub>3.3392</sub> <sub>ms</sub> | <sub>1.4740</sub> <sub>ms</sub> | <sub>0.2131</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>5.2218</sub> <sub>ms</sub> | <sub>3.9322</sub> <sub>ms</sub> | <sub>2.6183</sub> <sub>ms</sub> | <sub>0.2491</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>6.0518</sub> <sub>ms</sub> | <sub>4.4609</sub> <sub>ms</sub> | <sub>2.7022</sub> <sub>ms</sub> | <sub>0.2863</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>6.7873</sub> <sub>ms</sub> | <sub>5.0113</sub> <sub>ms</sub> | <sub>2.8715</sub> <sub>ms</sub> | <sub>0.3256</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>7.5296</sub> <sub>ms</sub> | <sub>5.7431</sub> <sub>ms</sub> | <sub>2.9658</sub> <sub>ms</sub> | <sub>0.3644</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>insert_random</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0843</sub> <sub>ms</sub> | <sub>0.0603</sub> <sub>ms</sub> | <sub>0.0429</sub> <sub>ms</sub> | <sub>0.0068</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4438</sub> <sub>ms</sub> | <sub>0.3309</sub> <sub>ms</sub> | <sub>0.2518</sub> <sub>ms</sub> | <sub>0.0628</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.9009</sub> <sub>ms</sub> | <sub>0.6314</sub> <sub>ms</sub> | <sub>0.5090</sub> <sub>ms</sub> | <sub>0.1331</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>1.9797</sub> <sub>ms</sub> | <sub>1.4348</sub> <sub>ms</sub> | <sub>0.9842</sub> <sub>ms</sub> | <sub>0.2759</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>2.7377</sub> <sub>ms</sub> | <sub>2.0729</sub> <sub>ms</sub> | <sub>1.2523</sub> <sub>ms</sub> | <sub>0.3369</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>3.8746</sub> <sub>ms</sub> | <sub>2.7678</sub> <sub>ms</sub> | <sub>2.2103</sub> <sub>ms</sub> | <sub>0.5789</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>5.0948</sub> <sub>ms</sub> | <sub>3.5740</sub> <sub>ms</sub> | <sub>2.5656</sub> <sub>ms</sub> | <sub>0.9881</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>5.8265</sub> <sub>ms</sub> | <sub>4.4193</sub> <sub>ms</sub> | <sub>3.1766</sub> <sub>ms</sub> | <sub>0.7385</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>7.0783</sub> <sub>ms</sub> | <sub>5.5233</sub> <sub>ms</sub> | <sub>5.1064</sub> <sub>ms</sub> | <sub>0.9586</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>8.4539</sub> <sub>ms</sub> | <sub>6.5921</sub> <sub>ms</sub> | <sub>5.6109</sub> <sub>ms</sub> | <sub>1.2523</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>9.9211</sub> <sub>ms</sub> | <sub>8.0280</sub> <sub>ms</sub> | <sub>6.0366</sub> <sub>ms</sub> | <sub>1.6028</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>11.4469</sub> <sub>ms</sub> | <sub>8.8643</sub> <sub>ms</sub> | <sub>6.9379</sub> <sub>ms</sub> | <sub>2.0809</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_sequential</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0177</sub> <sub>ms</sub> | <sub>0.0113</sub> <sub>ms</sub> | <sub>0.0097</sub> <sub>ms</sub> | <sub>0.0016</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0893</sub> <sub>ms</sub> | <sub>0.0600</sub> <sub>ms</sub> | <sub>0.0413</sub> <sub>ms</sub> | <sub>0.0082</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.1788</sub> <sub>ms</sub> | <sub>0.1236</sub> <sub>ms</sub> | <sub>0.0826</sub> <sub>ms</sub> | <sub>0.0210</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.3776</sub> <sub>ms</sub> | <sub>0.2265</sub> <sub>ms</sub> | <sub>0.1702</sub> <sub>ms</sub> | <sub>0.0327</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.5319</sub> <sub>ms</sub> | <sub>0.3423</sub> <sub>ms</sub> | <sub>0.2339</sub> <sub>ms</sub> | <sub>0.0480</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>0.7121</sub> <sub>ms</sub> | <sub>0.4536</sub> <sub>ms</sub> | <sub>0.3119</sub> <sub>ms</sub> | <sub>0.0711</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>0.8964</sub> <sub>ms</sub> | <sub>0.5698</sub> <sub>ms</sub> | <sub>0.3898</sub> <sub>ms</sub> | <sub>0.0835</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>1.0669</sub> <sub>ms</sub> | <sub>0.6877</sub> <sub>ms</sub> | <sub>0.4678</sub> <sub>ms</sub> | <sub>0.1030</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>1.2553</sub> <sub>ms</sub> | <sub>0.7983</sub> <sub>ms</sub> | <sub>0.5458</sub> <sub>ms</sub> | <sub>0.1274</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>1.4356</sub> <sub>ms</sub> | <sub>0.9133</sub> <sub>ms</sub> | <sub>0.6237</sub> <sub>ms</sub> | <sub>0.1578</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>1.6193</sub> <sub>ms</sub> | <sub>1.0386</sub> <sub>ms</sub> | <sub>0.7018</sub> <sub>ms</sub> | <sub>0.2070</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>1.8113</sub> <sub>ms</sub> | <sub>1.1549</sub> <sub>ms</sub> | <sub>0.7804</sub> <sub>ms</sub> | <sub>0.2674</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_random</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0301</sub> <sub>ms</sub> | <sub>0.0161</sub> <sub>ms</sub> | <sub>0.0146</sub> <sub>ms</sub> | <sub>0.0056</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.1407</sub> <sub>ms</sub> | <sub>0.0929</sub> <sub>ms</sub> | <sub>0.0539</sub> <sub>ms</sub> | <sub>0.0426</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.3350</sub> <sub>ms</sub> | <sub>0.1960</sub> <sub>ms</sub> | <sub>0.1165</sub> <sub>ms</sub> | <sub>0.0996</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.6900</sub> <sub>ms</sub> | <sub>0.4095</sub> <sub>ms</sub> | <sub>0.2186</sub> <sub>ms</sub> | <sub>0.1996</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>1.0036</sub> <sub>ms</sub> | <sub>0.7450</sub> <sub>ms</sub> | <sub>0.3972</sub> <sub>ms</sub> | <sub>0.2191</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>1.4414</sub> <sub>ms</sub> | <sub>0.8676</sub> <sub>ms</sub> | <sub>0.4482</sub> <sub>ms</sub> | <sub>0.4200</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>2.5247</sub> <sub>ms</sub> | <sub>1.1876</sub> <sub>ms</sub> | <sub>0.6227</sub> <sub>ms</sub> | <sub>0.8074</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>2.4953</sub> <sub>ms</sub> | <sub>1.7026</sub> <sub>ms</sub> | <sub>0.8350</sub> <sub>ms</sub> | <sub>0.6544</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>2.9197</sub> <sub>ms</sub> | <sub>2.4427</sub> <sub>ms</sub> | <sub>1.1728</sub> <sub>ms</sub> | <sub>0.9463</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>4.2765</sub> <sub>ms</sub> | <sub>3.4136</sub> <sub>ms</sub> | <sub>1.5378</sub> <sub>ms</sub> | <sub>1.2549</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>5.5896</sub> <sub>ms</sub> | <sub>4.2591</sub> <sub>ms</sub> | <sub>1.8384</sub> <sub>ms</sub> | <sub>1.6729</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>7.1952</sub> <sub>ms</sub> | <sub>5.4473</sub> <sub>ms</sub> | <sub>2.1147</sub> <sub>ms</sub> | <sub>2.2284</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_sequential</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1163</sub> <sub>ms</sub> | <sub>0.0676</sub> <sub>ms</sub> | <sub>0.0108</sub> <sub>ms</sub> | <sub>0.0059</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4968</sub> <sub>ms</sub> | <sub>0.3547</sub> <sub>ms</sub> | <sub>0.0458</sub> <sub>ms</sub> | <sub>0.0293</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.9422</sub> <sub>ms</sub> | <sub>0.6676</sub> <sub>ms</sub> | <sub>0.0915</sub> <sub>ms</sub> | <sub>0.0621</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>1.8745</sub> <sub>ms</sub> | <sub>1.3340</sub> <sub>ms</sub> | <sub>0.1727</sub> <sub>ms</sub> | <sub>0.1175</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>2.8132</sub> <sub>ms</sub> | <sub>2.0195</sub> <sub>ms</sub> | <sub>0.2591</sub> <sub>ms</sub> | <sub>0.1764</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>4.1210</sub> <sub>ms</sub> | <sub>3.0142</sub> <sub>ms</sub> | <sub>0.4288</sub> <sub>ms</sub> | <sub>0.2353</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>4.9241</sub> <sub>ms</sub> | <sub>3.4096</sub> <sub>ms</sub> | <sub>0.4590</sub> <sub>ms</sub> | <sub>0.3471</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>6.3164</sub> <sub>ms</sub> | <sub>4.7488</sub> <sub>ms</sub> | <sub>0.5653</sub> <sub>ms</sub> | <sub>0.3538</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>7.5258</sub> <sub>ms</sub> | <sub>5.2733</sub> <sub>ms</sub> | <sub>0.6047</sub> <sub>ms</sub> | <sub>0.4147</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>7.8778</sub> <sub>ms</sub> | <sub>5.8007</sub> <sub>ms</sub> | <sub>0.6912</sub> <sub>ms</sub> | <sub>0.4753</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>9.9224</sub> <sub>ms</sub> | <sub>6.8211</sub> <sub>ms</sub> | <sub>0.7782</sub> <sub>ms</sub> | <sub>0.5369</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>10.5752</sub> <sub>ms</sub> | <sub>7.6171</sub> <sub>ms</sub> | <sub>0.8645</sub> <sub>ms</sub> | <sub>0.6019</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_random</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1489</sub> <sub>ms</sub> | <sub>0.0815</sub> <sub>ms</sub> | <sub>0.0140</sub> <sub>ms</sub> | <sub>0.0133</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.6470</sub> <sub>ms</sub> | <sub>0.4311</sub> <sub>ms</sub> | <sub>0.0592</sub> <sub>ms</sub> | <sub>0.0830</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.2890</sub> <sub>ms</sub> | <sub>0.8749</sub> <sub>ms</sub> | <sub>0.1238</sub> <sub>ms</sub> | <sub>0.1899</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.7192</sub> <sub>ms</sub> | <sub>1.7815</sub> <sub>ms</sub> | <sub>0.2404</sub> <sub>ms</sub> | <sub>0.3774</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.0768</sub> <sub>ms</sub> | <sub>2.8051</sub> <sub>ms</sub> | <sub>0.4367</sub> <sub>ms</sub> | <sub>0.4950</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.6845</sub> <sub>ms</sub> | <sub>4.0814</sub> <sub>ms</sub> | <sub>0.4974</sub> <sub>ms</sub> | <sub>0.7808</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>7.6621</sub> <sub>ms</sub> | <sub>5.4839</sub> <sub>ms</sub> | <sub>0.6856</sub> <sub>ms</sub> | <sub>1.1835</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>10.1733</sub> <sub>ms</sub> | <sub>7.2761</sub> <sub>ms</sub> | <sub>0.9214</sub> <sub>ms</sub> | <sub>1.4106</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>12.6273</sub> <sub>ms</sub> | <sub>9.6829</sub> <sub>ms</sub> | <sub>1.4435</sub> <sub>ms</sub> | <sub>1.7645</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>16.0253</sub> <sub>ms</sub> | <sub>12.9931</sub> <sub>ms</sub> | <sub>1.8665</sub> <sub>ms</sub> | <sub>2.1905</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>18.9621</sub> <sub>ms</sub> | <sub>14.8710</sub> <sub>ms</sub> | <sub>2.0574</sub> <sub>ms</sub> | <sub>2.6278</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>22.3784</sub> <sub>ms</sub> | <sub>18.8374</sub> <sub>ms</sub> | <sub>2.7495</sub> <sub>ms</sub> | <sub>3.1805</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>iterator</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0032</sub> <sub>ms</sub> | <sub>0.0079</sub> <sub>ms</sub> | <sub>0.0081</sub> <sub>ms</sub> | <sub>0.0026</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0205</sub> <sub>ms</sub> | <sub>0.0442</sub> <sub>ms</sub> | <sub>0.0544</sub> <sub>ms</sub> | <sub>0.0258</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.0502</sub> <sub>ms</sub> | <sub>0.0904</sub> <sub>ms</sub> | <sub>0.1092</sub> <sub>ms</sub> | <sub>0.0598</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.1363</sub> <sub>ms</sub> | <sub>0.1895</sub> <sub>ms</sub> | <sub>0.2067</sub> <sub>ms</sub> | <sub>0.1189</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.2265</sub> <sub>ms</sub> | <sub>0.2534</sub> <sub>ms</sub> | <sub>0.2541</sub> <sub>ms</sub> | <sub>0.2598</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>0.3006</sub> <sub>ms</sub> | <sub>0.3883</sub> <sub>ms</sub> | <sub>0.4147</sub> <sub>ms</sub> | <sub>0.2487</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>0.3913</sub> <sub>ms</sub> | <sub>0.4679</sub> <sub>ms</sub> | <sub>0.4753</sub> <sub>ms</sub> | <sub>0.2299</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>0.5561</sub> <sub>ms</sub> | <sub>0.6008</sub> <sub>ms</sub> | <sub>0.5113</sub> <sub>ms</sub> | <sub>0.6166</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>0.7455</sub> <sub>ms</sub> | <sub>0.8100</sub> <sub>ms</sub> | <sub>0.8256</sub> <sub>ms</sub> | <sub>0.6834</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>1.0776</sub> <sub>ms</sub> | <sub>1.0297</sub> <sub>ms</sub> | <sub>0.8967</sub> <sub>ms</sub> | <sub>0.6967</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>1.5356</sub> <sub>ms</sub> | <sub>1.1963</sub> <sub>ms</sub> | <sub>0.9624</sub> <sub>ms</sub> | <sub>0.7686</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>1.7790</sub> <sub>ms</sub> | <sub>1.3773</sub> <sub>ms</sub> | <sub>1.0232</sub> <sub>ms</sub> | <sub>0.7800</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>create_insert_sum</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.2122</sub> <sub>ms</sub> | <sub>0.1301</sub> <sub>ms</sub> | <sub>0.0201</sub> <sub>ms</sub> | <sub>0.0216</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.7308</sub> <sub>ms</sub> | <sub>0.6744</sub> <sub>ms</sub> | <sub>0.1156</sub> <sub>ms</sub> | <sub>0.0984</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.3887</sub> <sub>ms</sub> | <sub>1.3445</sub> <sub>ms</sub> | <sub>0.2298</sub> <sub>ms</sub> | <sub>0.2290</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.7503</sub> <sub>ms</sub> | <sub>2.5309</sub> <sub>ms</sub> | <sub>0.4327</sub> <sub>ms</sub> | <sub>0.4628</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.2449</sub> <sub>ms</sub> | <sub>3.7071</sub> <sub>ms</sub> | <sub>0.6488</sub> <sub>ms</sub> | <sub>0.8317</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.6271</sub> <sub>ms</sub> | <sub>5.5578</sub> <sub>ms</sub> | <sub>0.8655</sub> <sub>ms</sub> | <sub>0.8332</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>6.9252</sub> <sub>ms</sub> | <sub>7.0277</sub> <sub>ms</sub> | <sub>1.0783</sub> <sub>ms</sub> | <sub>0.9410</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>9.0158</sub> <sub>ms</sub> | <sub>8.2026</sub> <sub>ms</sub> | <sub>1.1881</sub> <sub>ms</sub> | <sub>1.5785</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>10.3599</sub> <sub>ms</sub> | <sub>10.0722</sub> <sub>ms</sub> | <sub>1.6243</sub> <sub>ms</sub> | <sub>1.6685</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>11.5276</sub> <sub>ms</sub> | <sub>11.0100</sub> <sub>ms</sub> | <sub>1.8028</sub> <sub>ms</sub> | <sub>1.7572</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>13.0325</sub> <sub>ms</sub> | <sub>12.6680</sub> <sub>ms</sub> | <sub>2.2081</sub> <sub>ms</sub> | <sub>1.8682</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>14.2638</sub> <sub>ms</sub> | <sub>14.6805</sub> <sub>ms</sub> | <sub>2.1132</sub> <sub>ms</sub> | <sub>2.1902</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>adds_and_removes</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.9393</sub> <sub>ms</sub> | <sub>0.6984</sub> <sub>ms</sub> | <sub>0.4215</sub> <sub>ms</sub> | <sub>0.3516</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>4.5278</sub> <sub>ms</sub> | <sub>3.3578</sub> <sub>ms</sub> | <sub>2.2425</sub> <sub>ms</sub> | <sub>1.6678</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>9.4647</sub> <sub>ms</sub> | <sub>7.1207</sub> <sub>ms</sub> | <sub>4.7898</sub> <sub>ms</sub> | <sub>3.9096</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>23.6861</sub> <sub>ms</sub> | <sub>16.6999</sub> <sub>ms</sub> | <sub>10.8760</sub> <sub>ms</sub> | <sub>9.1180</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>33.0922</sub> <sub>ms</sub> | <sub>24.8726</sub> <sub>ms</sub> | <sub>14.1048</sub> <sub>ms</sub> | <sub>12.5556</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>52.6478</sub> <sub>ms</sub> | <sub>34.7545</sub> <sub>ms</sub> | <sub>24.0846</sub> <sub>ms</sub> | <sub>19.5040</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>66.3096</sub> <sub>ms</sub> | <sub>49.4562</sub> <sub>ms</sub> | <sub>30.5494</sub> <sub>ms</sub> | <sub>27.4240</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>78.3686</sub> <sub>ms</sub> | <sub>65.6828</sub> <sub>ms</sub> | <sub>31.6678</sub> <sub>ms</sub> | <sub>32.2304</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>106.8312</sub> <sub>ms</sub> | <sub>75.7957</sub> <sub>ms</sub> | <sub>44.9793</sub> <sub>ms</sub> | <sub>40.7407</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>154.6510</sub> <sub>ms</sub> | <sub>107.6227</sub> <sub>ms</sub> | <sub>69.2244</sub> <sub>ms</sub> | <sub>56.5548</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>152.6537</sub> <sub>ms</sub> | <sub>107.8968</sub> <sub>ms</sub> | <sub>75.8551</sub> <sub>ms</sub> | <sub>54.8880</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>226.9553</sub> <sub>ms</sub> | <sub>164.1412</sub> <sub>ms</sub> | <sub>92.4713</sub> <sub>ms</sub> | <sub>79.4711</sub> <sub>ms</sub> |



### log_new_big_2.txt
<sub>
## <sub>Timings</sub> <sub>insert_sequential</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0817</sub> <sub>ms</sub> | <sub>0.0650</sub> <sub>ms</sub> | <sub>0.0925</sub> <sub>ms</sub> | <sub>0.0186</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4141</sub> <sub>ms</sub> | <sub>0.3257</sub> <sub>ms</sub> | <sub>0.7550</sub> <sub>ms</sub> | <sub>0.1018</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.8764</sub> <sub>ms</sub> | <sub>0.6964</sub> <sub>ms</sub> | <sub>2.6578</sub> <sub>ms</sub> | <sub>0.1870</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>1.8603</sub> <sub>ms</sub> | <sub>1.5539</sub> <sub>ms</sub> | <sub>6.3872</sub> <sub>ms</sub> | <sub>0.4122</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>2.9049</sub> <sub>ms</sub> | <sub>2.3642</sub> <sub>ms</sub> | <sub>6.6289</sub> <sub>ms</sub> | <sub>0.6646</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>3.9013</sub> <sub>ms</sub> | <sub>3.2305</sub> <sub>ms</sub> | <sub>13.9324</sub> <sub>ms</sub> | <sub>0.8913</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>5.1210</sub> <sub>ms</sub> | <sub>4.3162</sub> <sub>ms</sub> | <sub>13.9558</sub> <sub>ms</sub> | <sub>1.1196</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>6.5457</sub> <sub>ms</sub> | <sub>5.6938</sub> <sub>ms</sub> | <sub>14.0992</sub> <sub>ms</sub> | <sub>1.3866</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>7.9718</sub> <sub>ms</sub> | <sub>6.7024</sub> <sub>ms</sub> | <sub>27.2777</sub> <sub>ms</sub> | <sub>1.6278</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>9.5970</sub> <sub>ms</sub> | <sub>7.9143</sub> <sub>ms</sub> | <sub>27.6991</sub> <sub>ms</sub> | <sub>1.8251</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>10.6715</sub> <sub>ms</sub> | <sub>9.1174</sub> <sub>ms</sub> | <sub>28.4876</sub> <sub>ms</sub> | <sub>2.0602</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>12.3267</sub> <sub>ms</sub> | <sub>10.4896</sub> <sub>ms</sub> | <sub>28.8851</sub> <sub>ms</sub> | <sub>2.2834</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>insert_random</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0935</sub> <sub>ms</sub> | <sub>0.0721</sub> <sub>ms</sub> | <sub>0.1015</sub> <sub>ms</sub> | <sub>0.0227</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.5190</sub> <sub>ms</sub> | <sub>0.3771</sub> <sub>ms</sub> | <sub>0.9303</sub> <sub>ms</sub> | <sub>0.1352</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.1173</sub> <sub>ms</sub> | <sub>0.8298</sub> <sub>ms</sub> | <sub>3.1572</sub> <sub>ms</sub> | <sub>0.2887</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.6000</sub> <sub>ms</sub> | <sub>2.1041</sub> <sub>ms</sub> | <sub>7.8836</sub> <sub>ms</sub> | <sub>0.6493</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.2702</sub> <sub>ms</sub> | <sub>3.6356</sub> <sub>ms</sub> | <sub>9.0574</sub> <sub>ms</sub> | <sub>1.0245</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>6.2078</sub> <sub>ms</sub> | <sub>5.3776</sub> <sub>ms</sub> | <sub>18.0498</sub> <sub>ms</sub> | <sub>1.4532</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>9.0387</sub> <sub>ms</sub> | <sub>7.1129</sub> <sub>ms</sub> | <sub>18.9887</sub> <sub>ms</sub> | <sub>2.0115</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>11.4306</sub> <sub>ms</sub> | <sub>9.6349</sub> <sub>ms</sub> | <sub>20.1558</sub> <sub>ms</sub> | <sub>2.9407</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>14.3796</sub> <sub>ms</sub> | <sub>11.9096</sub> <sub>ms</sub> | <sub>35.8712</sub> <sub>ms</sub> | <sub>3.5263</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>17.3189</sub> <sub>ms</sub> | <sub>14.4953</sub> <sub>ms</sub> | <sub>37.2538</sub> <sub>ms</sub> | <sub>4.1066</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>21.4086</sub> <sub>ms</sub> | <sub>16.4486</sub> <sub>ms</sub> | <sub>39.6225</sub> <sub>ms</sub> | <sub>4.7559</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>24.3082</sub> <sub>ms</sub> | <sub>18.9919</sub> <sub>ms</sub> | <sub>40.8574</sub> <sub>ms</sub> | <sub>5.6226</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_sequential</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0178</sub> <sub>ms</sub> | <sub>0.0114</sub> <sub>ms</sub> | <sub>0.0078</sub> <sub>ms</sub> | <sub>0.0027</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0894</sub> <sub>ms</sub> | <sub>0.0566</sub> <sub>ms</sub> | <sub>0.0485</sub> <sub>ms</sub> | <sub>0.0152</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.1809</sub> <sub>ms</sub> | <sub>0.1143</sub> <sub>ms</sub> | <sub>0.0886</sub> <sub>ms</sub> | <sub>0.0404</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.3848</sub> <sub>ms</sub> | <sub>0.2938</sub> <sub>ms</sub> | <sub>0.2181</sub> <sub>ms</sub> | <sub>0.1794</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.6409</sub> <sub>ms</sub> | <sub>0.4867</sub> <sub>ms</sub> | <sub>0.3516</sub> <sub>ms</sub> | <sub>0.3388</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>0.8854</sub> <sub>ms</sub> | <sub>0.7023</sub> <sub>ms</sub> | <sub>0.5400</sub> <sub>ms</sub> | <sub>0.3755</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>1.1246</sub> <sub>ms</sub> | <sub>0.8503</sub> <sub>ms</sub> | <sub>0.6571</sub> <sub>ms</sub> | <sub>0.4640</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>1.3567</sub> <sub>ms</sub> | <sub>1.0966</sub> <sub>ms</sub> | <sub>0.8490</sub> <sub>ms</sub> | <sub>0.5327</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>1.7394</sub> <sub>ms</sub> | <sub>1.1785</sub> <sub>ms</sub> | <sub>1.0189</sub> <sub>ms</sub> | <sub>0.6580</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>1.8949</sub> <sub>ms</sub> | <sub>1.3728</sub> <sub>ms</sub> | <sub>1.1457</sub> <sub>ms</sub> | <sub>0.8052</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>2.0727</sub> <sub>ms</sub> | <sub>1.5319</sub> <sub>ms</sub> | <sub>1.2624</sub> <sub>ms</sub> | <sub>0.8609</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>2.3399</sub> <sub>ms</sub> | <sub>1.7223</sub> <sub>ms</sub> | <sub>1.3652</sub> <sub>ms</sub> | <sub>1.0016</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_random</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0256</sub> <sub>ms</sub> | <sub>0.0168</sub> <sub>ms</sub> | <sub>0.0124</sub> <sub>ms</sub> | <sub>0.0061</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.1648</sub> <sub>ms</sub> | <sub>0.1223</sub> <sub>ms</sub> | <sub>0.0586</sub> <sub>ms</sub> | <sub>0.0571</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.3526</sub> <sub>ms</sub> | <sub>0.2104</sub> <sub>ms</sub> | <sub>0.1955</sub> <sub>ms</sub> | <sub>0.1098</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.9081</sub> <sub>ms</sub> | <sub>0.6020</sub> <sub>ms</sub> | <sub>0.4407</sub> <sub>ms</sub> | <sub>0.2914</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>1.8936</sub> <sub>ms</sub> | <sub>1.3779</sub> <sub>ms</sub> | <sub>1.0402</sub> <sub>ms</sub> | <sub>0.5090</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>3.1961</sub> <sub>ms</sub> | <sub>2.1063</sub> <sub>ms</sub> | <sub>1.4325</sub> <sub>ms</sub> | <sub>0.8081</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>4.6811</sub> <sub>ms</sub> | <sub>3.0359</sub> <sub>ms</sub> | <sub>1.9717</sub> <sub>ms</sub> | <sub>1.1360</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>6.1330</sub> <sub>ms</sub> | <sub>4.0557</sub> <sub>ms</sub> | <sub>2.6413</sub> <sub>ms</sub> | <sub>1.3465</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>7.6238</sub> <sub>ms</sub> | <sub>4.8197</sub> <sub>ms</sub> | <sub>2.8078</sub> <sub>ms</sub> | <sub>1.6204</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>9.1128</sub> <sub>ms</sub> | <sub>5.8012</sub> <sub>ms</sub> | <sub>3.2839</sub> <sub>ms</sub> | <sub>2.0316</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>11.2427</sub> <sub>ms</sub> | <sub>6.8202</sub> <sub>ms</sub> | <sub>3.7936</sub> <sub>ms</sub> | <sub>2.3135</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>12.8585</sub> <sub>ms</sub> | <sub>8.0152</sub> <sub>ms</sub> | <sub>4.5385</sub> <sub>ms</sub> | <sub>2.9190</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_sequential</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0976</sub> <sub>ms</sub> | <sub>0.0689</sub> <sub>ms</sub> | <sub>0.0087</sub> <sub>ms</sub> | <sub>0.0083</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4791</sub> <sub>ms</sub> | <sub>0.3419</sub> <sub>ms</sub> | <sub>0.0433</sub> <sub>ms</sub> | <sub>0.0444</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.2083</sub> <sub>ms</sub> | <sub>0.9391</sub> <sub>ms</sub> | <sub>0.1123</sub> <sub>ms</sub> | <sub>0.1032</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.3402</sub> <sub>ms</sub> | <sub>1.8592</sub> <sub>ms</sub> | <sub>0.2843</sub> <sub>ms</sub> | <sub>0.2126</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>3.6281</sub> <sub>ms</sub> | <sub>3.2249</sub> <sub>ms</sub> | <sub>0.5333</sub> <sub>ms</sub> | <sub>0.4045</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.8909</sub> <sub>ms</sub> | <sub>4.1933</sub> <sub>ms</sub> | <sub>0.7714</sub> <sub>ms</sub> | <sub>0.5739</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>6.6281</sub> <sub>ms</sub> | <sub>5.9014</sub> <sub>ms</sub> | <sub>0.9793</sub> <sub>ms</sub> | <sub>0.6781</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>8.3104</sub> <sub>ms</sub> | <sub>7.4879</sub> <sub>ms</sub> | <sub>1.2077</sub> <sub>ms</sub> | <sub>0.8237</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>9.3395</sub> <sub>ms</sub> | <sub>8.3768</sub> <sub>ms</sub> | <sub>1.7053</sub> <sub>ms</sub> | <sub>0.9665</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>10.4567</sub> <sub>ms</sub> | <sub>9.1555</sub> <sub>ms</sub> | <sub>1.6712</sub> <sub>ms</sub> | <sub>1.1396</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>11.5906</sub> <sub>ms</sub> | <sub>11.2852</sub> <sub>ms</sub> | <sub>2.1537</sub> <sub>ms</sub> | <sub>1.2740</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>13.7190</sub> <sub>ms</sub> | <sub>11.4848</sub> <sub>ms</sub> | <sub>2.3893</sub> <sub>ms</sub> | <sub>1.4794</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_random</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1220</sub> <sub>ms</sub> | <sub>0.1034</sub> <sub>ms</sub> | <sub>0.0136</sub> <sub>ms</sub> | <sub>0.0139</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.6684</sub> <sub>ms</sub> | <sub>0.4454</sub> <sub>ms</sub> | <sub>0.0625</sub> <sub>ms</sub> | <sub>0.1038</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.8116</sub> <sub>ms</sub> | <sub>1.2929</sub> <sub>ms</sub> | <sub>0.1813</sub> <sub>ms</sub> | <sub>0.2532</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>4.7037</sub> <sub>ms</sub> | <sub>3.3459</sub> <sub>ms</sub> | <sub>0.5242</sub> <sub>ms</sub> | <sub>0.4019</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>8.5488</sub> <sub>ms</sub> | <sub>5.8824</sub> <sub>ms</sub> | <sub>1.0942</sub> <sub>ms</sub> | <sub>0.6856</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>12.8873</sub> <sub>ms</sub> | <sub>10.1513</sub> <sub>ms</sub> | <sub>1.4431</sub> <sub>ms</sub> | <sub>1.0199</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>18.1364</sub> <sub>ms</sub> | <sub>13.8885</sub> <sub>ms</sub> | <sub>2.0565</sub> <sub>ms</sub> | <sub>1.3868</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>24.1655</sub> <sub>ms</sub> | <sub>17.5640</sub> <sub>ms</sub> | <sub>2.8903</sub> <sub>ms</sub> | <sub>2.2231</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>29.2004</sub> <sub>ms</sub> | <sub>21.8310</sub> <sub>ms</sub> | <sub>3.1725</sub> <sub>ms</sub> | <sub>2.6203</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>35.2444</sub> <sub>ms</sub> | <sub>25.7679</sub> <sub>ms</sub> | <sub>3.7122</sub> <sub>ms</sub> | <sub>3.1974</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>41.7119</sub> <sub>ms</sub> | <sub>30.2688</sub> <sub>ms</sub> | <sub>4.4452</sub> <sub>ms</sub> | <sub>3.4161</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>48.7243</sub> <sub>ms</sub> | <sub>35.2759</sub> <sub>ms</sub> | <sub>5.0931</sub> <sub>ms</sub> | <sub>4.3798</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>iterator</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0033</sub> <sub>ms</sub> | <sub>0.0100</sub> <sub>ms</sub> | <sub>0.0054</sub> <sub>ms</sub> | <sub>0.0028</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0424</sub> <sub>ms</sub> | <sub>0.0472</sub> <sub>ms</sub> | <sub>0.0635</sub> <sub>ms</sub> | <sub>0.0321</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.0944</sub> <sub>ms</sub> | <sub>0.1018</sub> <sub>ms</sub> | <sub>0.2051</sub> <sub>ms</sub> | <sub>0.2014</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.2534</sub> <sub>ms</sub> | <sub>0.2185</sub> <sub>ms</sub> | <sub>0.5633</sub> <sub>ms</sub> | <sub>0.2079</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.7163</sub> <sub>ms</sub> | <sub>0.3982</sub> <sub>ms</sub> | <sub>0.6474</sub> <sub>ms</sub> | <sub>0.4607</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>1.4403</sub> <sub>ms</sub> | <sub>0.5637</sub> <sub>ms</sub> | <sub>1.2319</sub> <sub>ms</sub> | <sub>0.5964</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>2.1424</sub> <sub>ms</sub> | <sub>0.9094</sub> <sub>ms</sub> | <sub>1.3030</sub> <sub>ms</sub> | <sub>0.6746</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>2.8459</sub> <sub>ms</sub> | <sub>1.1356</sub> <sub>ms</sub> | <sub>1.3311</sub> <sub>ms</sub> | <sub>1.0528</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>3.4208</sub> <sub>ms</sub> | <sub>1.3574</sub> <sub>ms</sub> | <sub>2.2785</sub> <sub>ms</sub> | <sub>1.5609</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>4.0502</sub> <sub>ms</sub> | <sub>1.5583</sub> <sub>ms</sub> | <sub>2.3301</sub> <sub>ms</sub> | <sub>1.6010</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>4.7007</sub> <sub>ms</sub> | <sub>1.7872</sub> <sub>ms</sub> | <sub>2.4275</sub> <sub>ms</sub> | <sub>1.8944</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>5.3841</sub> <sub>ms</sub> | <sub>1.9374</sub> <sub>ms</sub> | <sub>2.4488</sub> <sub>ms</sub> | <sub>2.0152</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>create_insert_sum</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1566</sub> <sub>ms</sub> | <sub>0.1505</sub> <sub>ms</sub> | <sub>0.0579</sub> <sub>ms</sub> | <sub>0.0871</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.8370</sub> <sub>ms</sub> | <sub>0.7384</sub> <sub>ms</sub> | <sub>0.3593</sub> <sub>ms</sub> | <sub>0.6591</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.6387</sub> <sub>ms</sub> | <sub>1.8967</sub> <sub>ms</sub> | <sub>1.9378</sub> <sub>ms</sub> | <sub>0.8680</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>3.8122</sub> <sub>ms</sub> | <sub>3.8780</sub> <sub>ms</sub> | <sub>4.1152</sub> <sub>ms</sub> | <sub>2.0864</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>6.5099</sub> <sub>ms</sub> | <sub>6.9293</sub> <sub>ms</sub> | <sub>4.7370</sub> <sub>ms</sub> | <sub>2.9761</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>8.5196</sub> <sub>ms</sub> | <sub>10.0456</sub> <sub>ms</sub> | <sub>7.8188</sub> <sub>ms</sub> | <sub>3.9875</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>10.5867</sub> <sub>ms</sub> | <sub>12.3761</sub> <sub>ms</sub> | <sub>8.3248</sub> <sub>ms</sub> | <sub>4.7950</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>14.9056</sub> <sub>ms</sub> | <sub>15.7301</sub> <sub>ms</sub> | <sub>8.7533</sub> <sub>ms</sub> | <sub>11.6301</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>17.1877</sub> <sub>ms</sub> | <sub>19.3867</sub> <sub>ms</sub> | <sub>15.7870</sub> <sub>ms</sub> | <sub>12.2083</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>20.3840</sub> <sub>ms</sub> | <sub>22.0050</sub> <sub>ms</sub> | <sub>16.6590</sub> <sub>ms</sub> | <sub>9.3987</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>24.5122</sub> <sub>ms</sub> | <sub>26.2979</sub> <sub>ms</sub> | <sub>16.6344</sub> <sub>ms</sub> | <sub>15.0467</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>26.8069</sub> <sub>ms</sub> | <sub>28.9473</sub> <sub>ms</sub> | <sub>17.0231</sub> <sub>ms</sub> | <sub>17.6091</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>adds_and_removes</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>1.0313</sub> <sub>ms</sub> | <sub>0.7918</sub> <sub>ms</sub> | <sub>0.6682</sub> <sub>ms</sub> | <sub>0.5154</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>4.9916</sub> <sub>ms</sub> | <sub>3.7127</sub> <sub>ms</sub> | <sub>3.6480</sub> <sub>ms</sub> | <sub>2.3779</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>10.8786</sub> <sub>ms</sub> | <sub>8.5341</sub> <sub>ms</sub> | <sub>13.2278</sub> <sub>ms</sub> | <sub>5.1179</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>28.9636</sub> <sub>ms</sub> | <sub>20.3147</sub> <sub>ms</sub> | <sub>42.0800</sub> <sub>ms</sub> | <sub>12.4721</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>46.4848</sub> <sub>ms</sub> | <sub>35.9475</sub> <sub>ms</sub> | <sub>27.0017</sub> <sub>ms</sub> | <sub>21.5278</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>82.0585</sub> <sub>ms</sub> | <sub>66.9440</sub> <sub>ms</sub> | <sub>89.9695</sub> <sub>ms</sub> | <sub>30.3698</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>137.0056</sub> <sub>ms</sub> | <sub>94.9345</sub> <sub>ms</sub> | <sub>119.4609</sub> <sub>ms</sub> | <sub>40.6443</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>177.1139</sub> <sub>ms</sub> | <sub>131.1162</sub> <sub>ms</sub> | <sub>77.7000</sub> <sub>ms</sub> | <sub>73.1107</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>213.9331</sub> <sub>ms</sub> | <sub>154.4811</sub> <sub>ms</sub> | <sub>136.7261</sub> <sub>ms</sub> | <sub>82.8069</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>299.6145</sub> <sub>ms</sub> | <sub>199.2533</sub> <sub>ms</sub> | <sub>223.6790</sub> <sub>ms</sub> | <sub>95.7404</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>300.7180</sub> <sub>ms</sub> | <sub>206.4389</sub> <sub>ms</sub> | <sub>254.2888</sub> <sub>ms</sub> | <sub>97.1851</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>383.4946</sub> <sub>ms</sub> | <sub>276.4177</sub> <sub>ms</sub> | <sub>254.8635</sub> <sub>ms</sub> | <sub>108.4383</sub> <sub>ms</sub> |


