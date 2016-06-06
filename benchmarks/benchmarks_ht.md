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

### log_new_small.txt
<sub>
## <sub>Timings</sub> <sub>insert_sequential</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0723</sub> <sub>ms</sub> | <sub>0.0582</sub> <sub>ms</sub> | <sub>0.0257</sub> <sub>ms</sub> | <sub>0.0256</sub> <sub>ms</sub> | <sub>0.0023</sub> <sub>ms</sub> | <sub>0.0033</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.3615</sub> <sub>ms</sub> | <sub>0.2742</sub> <sub>ms</sub> | <sub>0.1704</sub> <sub>ms</sub> | <sub>0.1038</sub> <sub>ms</sub> | <sub>0.0119</sub> <sub>ms</sub> | <sub>0.0163</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.7216</sub> <sub>ms</sub> | <sub>0.5337</sub> <sub>ms</sub> | <sub>0.2966</sub> <sub>ms</sub> | <sub>0.2082</sub> <sub>ms</sub> | <sub>0.0224</sub> <sub>ms</sub> | <sub>0.0383</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>1.4300</sub> <sub>ms</sub> | <sub>1.1070</sub> <sub>ms</sub> | <sub>0.5403</sub> <sub>ms</sub> | <sub>0.4157</sub> <sub>ms</sub> | <sub>0.0490</sub> <sub>ms</sub> | <sub>0.0866</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>2.1510</sub> <sub>ms</sub> | <sub>1.6634</sub> <sub>ms</sub> | <sub>0.6890</sub> <sub>ms</sub> | <sub>0.6203</sub> <sub>ms</sub> | <sub>0.0735</sub> <sub>ms</sub> | <sub>0.1048</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>2.8962</sub> <sub>ms</sub> | <sub>2.2549</sub> <sub>ms</sub> | <sub>1.2135</sub> <sub>ms</sub> | <sub>0.8308</sub> <sub>ms</sub> | <sub>0.0898</sub> <sub>ms</sub> | <sub>0.1394</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>3.6769</sub> <sub>ms</sub> | <sub>2.7779</sub> <sub>ms</sub> | <sub>1.3737</sub> <sub>ms</sub> | <sub>1.0405</sub> <sub>ms</sub> | <sub>0.1122</sub> <sub>ms</sub> | <sub>0.1741</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>4.4238</sub> <sub>ms</sub> | <sub>3.3522</sub> <sub>ms</sub> | <sub>1.5119</sub> <sub>ms</sub> | <sub>1.2417</sub> <sub>ms</sub> | <sub>0.1346</sub> <sub>ms</sub> | <sub>0.2127</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>5.2503</sub> <sub>ms</sub> | <sub>3.9114</sub> <sub>ms</sub> | <sub>2.6023</sub> <sub>ms</sub> | <sub>1.4483</sub> <sub>ms</sub> | <sub>0.1570</sub> <sub>ms</sub> | <sub>0.2505</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>6.0069</sub> <sub>ms</sub> | <sub>4.4804</sub> <sub>ms</sub> | <sub>2.7667</sub> <sub>ms</sub> | <sub>1.6677</sub> <sub>ms</sub> | <sub>0.1796</sub> <sub>ms</sub> | <sub>0.2884</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>6.7417</sub> <sub>ms</sub> | <sub>5.0077</sub> <sub>ms</sub> | <sub>2.9014</sub> <sub>ms</sub> | <sub>1.8741</sub> <sub>ms</sub> | <sub>0.2020</sub> <sub>ms</sub> | <sub>0.3261</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>7.6377</sub> <sub>ms</sub> | <sub>5.6871</sub> <sub>ms</sub> | <sub>2.9881</sub> <sub>ms</sub> | <sub>2.0860</sub> <sub>ms</sub> | <sub>0.2243</sub> <sub>ms</sub> | <sub>0.3629</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>insert_random</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0850</sub> <sub>ms</sub> | <sub>0.0610</sub> <sub>ms</sub> | <sub>0.0361</sub> <sub>ms</sub> | <sub>0.0302</sub> <sub>ms</sub> | <sub>0.0059</sub> <sub>ms</sub> | <sub>0.0062</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4455</sub> <sub>ms</sub> | <sub>0.3123</sub> <sub>ms</sub> | <sub>0.2542</sub> <sub>ms</sub> | <sub>0.1291</sub> <sub>ms</sub> | <sub>0.0603</sub> <sub>ms</sub> | <sub>0.0585</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.9065</sub> <sub>ms</sub> | <sub>0.6650</sub> <sub>ms</sub> | <sub>0.4738</sub> <sub>ms</sub> | <sub>0.2605</sub> <sub>ms</sub> | <sub>0.1249</sub> <sub>ms</sub> | <sub>0.1258</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>1.8841</sub> <sub>ms</sub> | <sub>1.3112</sub> <sub>ms</sub> | <sub>0.9644</sub> <sub>ms</sub> | <sub>0.5344</sub> <sub>ms</sub> | <sub>0.2758</sub> <sub>ms</sub> | <sub>0.2998</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>2.7637</sub> <sub>ms</sub> | <sub>2.0846</sub> <sub>ms</sub> | <sub>1.2285</sub> <sub>ms</sub> | <sub>0.8192</sub> <sub>ms</sub> | <sub>0.3206</sub> <sub>ms</sub> | <sub>0.3344</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>3.9695</sub> <sub>ms</sub> | <sub>2.7781</sub> <sub>ms</sub> | <sub>2.0969</sub> <sub>ms</sub> | <sub>1.1135</sub> <sub>ms</sub> | <sub>0.5807</sub> <sub>ms</sub> | <sub>0.5734</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>5.3110</sub> <sub>ms</sub> | <sub>3.5610</sub> <sub>ms</sub> | <sub>2.3905</sub> <sub>ms</sub> | <sub>1.4010</sub> <sub>ms</sub> | <sub>1.0099</sub> <sub>ms</sub> | <sub>0.9807</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>6.3150</sub> <sub>ms</sub> | <sub>4.4089</sub> <sub>ms</sub> | <sub>2.6853</sub> <sub>ms</sub> | <sub>1.7005</sub> <sub>ms</sub> | <sub>0.6809</sub> <sub>ms</sub> | <sub>0.7553</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>7.8195</sub> <sub>ms</sub> | <sub>5.4397</sub> <sub>ms</sub> | <sub>4.5490</sub> <sub>ms</sub> | <sub>1.9954</sub> <sub>ms</sub> | <sub>0.9210</sub> <sub>ms</sub> | <sub>0.9584</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>9.1941</sub> <sub>ms</sub> | <sub>6.6149</sub> <sub>ms</sub> | <sub>4.9757</sub> <sub>ms</sub> | <sub>2.2977</sub> <sub>ms</sub> | <sub>1.2082</sub> <sub>ms</sub> | <sub>1.2419</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>10.8048</sub> <sub>ms</sub> | <sub>7.7277</sub> <sub>ms</sub> | <sub>5.4312</sub> <sub>ms</sub> | <sub>2.6094</sub> <sub>ms</sub> | <sub>1.6001</sub> <sub>ms</sub> | <sub>1.6141</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>12.4751</sub> <sub>ms</sub> | <sub>8.9134</sub> <sub>ms</sub> | <sub>5.8575</sub> <sub>ms</sub> | <sub>2.9107</sub> <sub>ms</sub> | <sub>2.0896</sub> <sub>ms</sub> | <sub>2.0785</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_sequential</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0197</sub> <sub>ms</sub> | <sub>0.0115</sub> <sub>ms</sub> | <sub>0.0080</sub> <sub>ms</sub> | <sub>0.0108</sub> <sub>ms</sub> | <sub>0.0012</sub> <sub>ms</sub> | <sub>0.0016</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0926</sub> <sub>ms</sub> | <sub>0.0629</sub> <sub>ms</sub> | <sub>0.0410</sub> <sub>ms</sub> | <sub>0.0433</sub> <sub>ms</sub> | <sub>0.0061</sub> <sub>ms</sub> | <sub>0.0077</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.1851</sub> <sub>ms</sub> | <sub>0.1152</sub> <sub>ms</sub> | <sub>0.0752</sub> <sub>ms</sub> | <sub>0.0867</sub> <sub>ms</sub> | <sub>0.0124</sub> <sub>ms</sub> | <sub>0.0208</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.3708</sub> <sub>ms</sub> | <sub>0.2304</sub> <sub>ms</sub> | <sub>0.1641</sub> <sub>ms</sub> | <sub>0.1734</sub> <sub>ms</sub> | <sub>0.0250</sub> <sub>ms</sub> | <sub>0.0323</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.5543</sub> <sub>ms</sub> | <sub>0.3483</sub> <sub>ms</sub> | <sub>0.2256</sub> <sub>ms</sub> | <sub>0.2605</sub> <sub>ms</sub> | <sub>0.0371</sub> <sub>ms</sub> | <sub>0.0483</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>0.7410</sub> <sub>ms</sub> | <sub>0.4611</sub> <sub>ms</sub> | <sub>0.3007</sub> <sub>ms</sub> | <sub>0.3468</sub> <sub>ms</sub> | <sub>0.0495</sub> <sub>ms</sub> | <sub>0.0654</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>0.9330</sub> <sub>ms</sub> | <sub>0.5794</sub> <sub>ms</sub> | <sub>0.4101</sub> <sub>ms</sub> | <sub>0.4331</sub> <sub>ms</sub> | <sub>0.0671</sub> <sub>ms</sub> | <sub>0.0823</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>1.1145</sub> <sub>ms</sub> | <sub>0.6990</sub> <sub>ms</sub> | <sub>0.4511</sub> <sub>ms</sub> | <sub>0.5212</sub> <sub>ms</sub> | <sub>0.0748</sub> <sub>ms</sub> | <sub>0.1023</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>1.3085</sub> <sub>ms</sub> | <sub>0.8082</sub> <sub>ms</sub> | <sub>0.5263</sub> <sub>ms</sub> | <sub>0.6073</sub> <sub>ms</sub> | <sub>0.0868</sub> <sub>ms</sub> | <sub>0.1250</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>1.4981</sub> <sub>ms</sub> | <sub>0.9300</sub> <sub>ms</sub> | <sub>0.6016</sub> <sub>ms</sub> | <sub>0.6946</sub> <sub>ms</sub> | <sub>0.1104</sub> <sub>ms</sub> | <sub>0.1613</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>1.6885</sub> <sub>ms</sub> | <sub>1.0578</sub> <sub>ms</sub> | <sub>0.6769</sub> <sub>ms</sub> | <sub>0.7814</sub> <sub>ms</sub> | <sub>0.1135</sub> <sub>ms</sub> | <sub>0.2065</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>1.8760</sub> <sub>ms</sub> | <sub>1.1780</sub> <sub>ms</sub> | <sub>0.7523</sub> <sub>ms</sub> | <sub>0.8681</sub> <sub>ms</sub> | <sub>0.1284</sub> <sub>ms</sub> | <sub>0.2253</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_random</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0258</sub> <sub>ms</sub> | <sub>0.0160</sub> <sub>ms</sub> | <sub>0.0122</sub> <sub>ms</sub> | <sub>0.0166</sub> <sub>ms</sub> | <sub>0.0055</sub> <sub>ms</sub> | <sub>0.0056</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.1402</sub> <sub>ms</sub> | <sub>0.0876</sub> <sub>ms</sub> | <sub>0.0493</sub> <sub>ms</sub> | <sub>0.0751</sub> <sub>ms</sub> | <sub>0.0418</sub> <sub>ms</sub> | <sub>0.0432</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.3159</sub> <sub>ms</sub> | <sub>0.1935</sub> <sub>ms</sub> | <sub>0.1042</sub> <sub>ms</sub> | <sub>0.1995</sub> <sub>ms</sub> | <sub>0.0876</sub> <sub>ms</sub> | <sub>0.0944</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.6859</sub> <sub>ms</sub> | <sub>0.4065</sub> <sub>ms</sub> | <sub>0.2149</sub> <sub>ms</sub> | <sub>0.3489</sub> <sub>ms</sub> | <sub>0.2073</sub> <sub>ms</sub> | <sub>0.2002</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.9886</sub> <sub>ms</sub> | <sub>0.7209</sub> <sub>ms</sub> | <sub>0.3916</sub> <sub>ms</sub> | <sub>0.5462</sub> <sub>ms</sub> | <sub>0.1870</sub> <sub>ms</sub> | <sub>0.2276</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>1.4242</sub> <sub>ms</sub> | <sub>0.8501</sub> <sub>ms</sub> | <sub>0.4417</sub> <sub>ms</sub> | <sub>0.7478</sub> <sub>ms</sub> | <sub>0.3868</sub> <sub>ms</sub> | <sub>0.4309</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>1.9482</sub> <sub>ms</sub> | <sub>1.1720</sub> <sub>ms</sub> | <sub>0.6129</sub> <sub>ms</sub> | <sub>0.9386</sub> <sub>ms</sub> | <sub>0.7511</sub> <sub>ms</sub> | <sub>0.7987</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>2.2584</sub> <sub>ms</sub> | <sub>1.7080</sub> <sub>ms</sub> | <sub>0.8093</sub> <sub>ms</sub> | <sub>1.2465</sub> <sub>ms</sub> | <sub>0.4011</sub> <sub>ms</sub> | <sub>0.6777</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>3.3347</sub> <sub>ms</sub> | <sub>2.3828</sub> <sub>ms</sub> | <sub>1.1290</sub> <sub>ms</sub> | <sub>1.3916</sub> <sub>ms</sub> | <sub>0.5672</sub> <sub>ms</sub> | <sub>0.9513</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>4.3219</sub> <sub>ms</sub> | <sub>3.2972</sub> <sub>ms</sub> | <sub>1.4509</sub> <sub>ms</sub> | <sub>1.6839</sub> <sub>ms</sub> | <sub>0.8090</sub> <sub>ms</sub> | <sub>1.2768</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>5.5907</sub> <sub>ms</sub> | <sub>4.0735</sub> <sub>ms</sub> | <sub>2.1142</sub> <sub>ms</sub> | <sub>2.0523</sub> <sub>ms</sub> | <sub>1.1471</sub> <sub>ms</sub> | <sub>1.6849</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>7.1234</sub> <sub>ms</sub> | <sub>4.9756</sub> <sub>ms</sub> | <sub>2.2652</sub> <sub>ms</sub> | <sub>2.4598</sub> <sub>ms</sub> | <sub>1.6093</sub> <sub>ms</sub> | <sub>2.3456</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_sequential</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0946</sub> <sub>ms</sub> | <sub>0.0675</sub> <sub>ms</sub> | <sub>0.0087</sub> <sub>ms</sub> | <sub>0.0135</sub> <sub>ms</sub> | <sub>0.0048</sub> <sub>ms</sub> | <sub>0.0062</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4696</sub> <sub>ms</sub> | <sub>0.3377</sub> <sub>ms</sub> | <sub>0.0432</sub> <sub>ms</sub> | <sub>0.0549</sub> <sub>ms</sub> | <sub>0.0236</sub> <sub>ms</sub> | <sub>0.0307</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.9416</sub> <sub>ms</sub> | <sub>0.6734</sub> <sub>ms</sub> | <sub>0.0864</sub> <sub>ms</sub> | <sub>0.1098</sub> <sub>ms</sub> | <sub>0.0590</sub> <sub>ms</sub> | <sub>0.0614</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>1.8810</sub> <sub>ms</sub> | <sub>1.3566</sub> <sub>ms</sub> | <sub>0.1728</sub> <sub>ms</sub> | <sub>0.2198</sub> <sub>ms</sub> | <sub>0.1178</sub> <sub>ms</sub> | <sub>0.1229</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>2.8190</sub> <sub>ms</sub> | <sub>2.0215</sub> <sub>ms</sub> | <sub>0.2591</sub> <sub>ms</sub> | <sub>0.4066</sub> <sub>ms</sub> | <sub>0.1553</sub> <sub>ms</sub> | <sub>0.1847</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>4.1907</sub> <sub>ms</sub> | <sub>3.0967</sub> <sub>ms</sub> | <sub>0.3455</sub> <sub>ms</sub> | <sub>0.4399</sub> <sub>ms</sub> | <sub>0.1870</sub> <sub>ms</sub> | <sub>0.2473</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>5.3385</sub> <sub>ms</sub> | <sub>4.0358</sub> <sub>ms</sub> | <sub>0.4320</sub> <sub>ms</sub> | <sub>0.5533</sub> <sub>ms</sub> | <sub>0.2337</sub> <sub>ms</sub> | <sub>0.3090</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>6.3371</sub> <sub>ms</sub> | <sub>4.7263</sub> <sub>ms</sub> | <sub>0.5184</sub> <sub>ms</sub> | <sub>0.6560</sub> <sub>ms</sub> | <sub>0.2812</sub> <sub>ms</sub> | <sub>0.3706</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>7.6096</sub> <sub>ms</sub> | <sub>5.1887</sub> <sub>ms</sub> | <sub>0.6050</sub> <sub>ms</sub> | <sub>0.7679</sub> <sub>ms</sub> | <sub>0.3626</sub> <sub>ms</sub> | <sub>0.4331</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>7.8141</sub> <sub>ms</sub> | <sub>5.7064</sub> <sub>ms</sub> | <sub>0.6913</sub> <sub>ms</sub> | <sub>0.8820</sub> <sub>ms</sub> | <sub>0.3800</sub> <sub>ms</sub> | <sub>0.4966</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>9.3622</sub> <sub>ms</sub> | <sub>6.9189</sub> <sub>ms</sub> | <sub>0.7779</sub> <sub>ms</sub> | <sub>0.9971</sub> <sub>ms</sub> | <sub>0.4276</sub> <sub>ms</sub> | <sub>0.5628</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>10.9875</sub> <sub>ms</sub> | <sub>8.5806</sub> <sub>ms</sub> | <sub>0.9402</sub> <sub>ms</sub> | <sub>1.1107</sub> <sub>ms</sub> | <sub>0.4696</sub> <sub>ms</sub> | <sub>0.6266</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_random</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.1233</sub> <sub>ms</sub> | <sub>0.0822</sub> <sub>ms</sub> | <sub>0.0130</sub> <sub>ms</sub> | <sub>0.0149</sub> <sub>ms</sub> | <sub>0.0117</sub> <sub>ms</sub> | <sub>0.0137</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.6252</sub> <sub>ms</sub> | <sub>0.4517</sub> <sub>ms</sub> | <sub>0.0556</sub> <sub>ms</sub> | <sub>0.0744</sub> <sub>ms</sub> | <sub>0.0742</sub> <sub>ms</sub> | <sub>0.1055</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.3155</sub> <sub>ms</sub> | <sub>0.8647</sub> <sub>ms</sub> | <sub>0.1280</sub> <sub>ms</sub> | <sub>0.1531</sub> <sub>ms</sub> | <sub>0.1524</sub> <sub>ms</sub> | <sub>0.1847</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.7579</sub> <sub>ms</sub> | <sub>1.8158</sub> <sub>ms</sub> | <sub>0.2405</sub> <sub>ms</sub> | <sub>0.3302</sub> <sub>ms</sub> | <sub>0.3293</sub> <sub>ms</sub> | <sub>0.3887</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.2392</sub> <sub>ms</sub> | <sub>2.8281</sub> <sub>ms</sub> | <sub>0.4348</sub> <sub>ms</sub> | <sub>0.5164</sub> <sub>ms</sub> | <sub>0.4199</sub> <sub>ms</sub> | <sub>0.5146</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.8615</sub> <sub>ms</sub> | <sub>3.7954</sub> <sub>ms</sub> | <sub>0.4935</sub> <sub>ms</sub> | <sub>0.7226</sub> <sub>ms</sub> | <sub>0.6815</sub> <sub>ms</sub> | <sub>0.8111</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>7.8553</sub> <sub>ms</sub> | <sub>5.4267</sub> <sub>ms</sub> | <sub>0.6838</sub> <sub>ms</sub> | <sub>0.9034</sub> <sub>ms</sub> | <sub>1.0647</sub> <sub>ms</sub> | <sub>1.2148</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>10.0389</sub> <sub>ms</sub> | <sub>7.1807</sub> <sub>ms</sub> | <sub>0.9234</sub> <sub>ms</sub> | <sub>1.2646</sub> <sub>ms</sub> | <sub>0.9179</sub> <sub>ms</sub> | <sub>1.4016</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>12.7598</sub> <sub>ms</sub> | <sub>9.7843</sub> <sub>ms</sub> | <sub>1.4505</sub> <sub>ms</sub> | <sub>1.3648</sub> <sub>ms</sub> | <sub>1.1525</sub> <sub>ms</sub> | <sub>1.8831</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>15.2109</sub> <sub>ms</sub> | <sub>12.3859</sub> <sub>ms</sub> | <sub>1.7833</sub> <sub>ms</sub> | <sub>1.6763</sub> <sub>ms</sub> | <sub>1.4633</sub> <sub>ms</sub> | <sub>2.2873</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>19.3179</sub> <sub>ms</sub> | <sub>15.2619</sub> <sub>ms</sub> | <sub>2.3453</sub> <sub>ms</sub> | <sub>2.2007</sub> <sub>ms</sub> | <sub>1.7762</sub> <sub>ms</sub> | <sub>2.6980</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>22.7006</sub> <sub>ms</sub> | <sub>18.0609</sub> <sub>ms</sub> | <sub>2.4917</sub> <sub>ms</sub> | <sub>2.4598</sub> <sub>ms</sub> | <sub>2.2303</sub> <sub>ms</sub> | <sub>3.1907</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>iterator</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0022</sub> <sub>ms</sub> | <sub>0.0080</sub> <sub>ms</sub> | <sub>0.0072</sub> <sub>ms</sub> | <sub>0.0052</sub> <sub>ms</sub> | <sub>0.0027</sub> <sub>ms</sub> | <sub>0.0023</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0225</sub> <sub>ms</sub> | <sub>0.0423</sub> <sub>ms</sub> | <sub>0.0554</sub> <sub>ms</sub> | <sub>0.0422</sub> <sub>ms</sub> | <sub>0.0250</sub> <sub>ms</sub> | <sub>0.0279</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.0518</sub> <sub>ms</sub> | <sub>0.0925</sub> <sub>ms</sub> | <sub>0.1108</sub> <sub>ms</sub> | <sub>0.0842</sub> <sub>ms</sub> | <sub>0.0573</sub> <sub>ms</sub> | <sub>0.0567</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.1322</sub> <sub>ms</sub> | <sub>0.1917</sub> <sub>ms</sub> | <sub>0.2205</sub> <sub>ms</sub> | <sub>0.1801</sub> <sub>ms</sub> | <sub>0.1285</sub> <sub>ms</sub> | <sub>0.1192</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.2262</sub> <sub>ms</sub> | <sub>0.2543</sub> <sub>ms</sub> | <sub>0.2677</sub> <sub>ms</sub> | <sub>0.2784</sub> <sub>ms</sub> | <sub>0.2496</sub> <sub>ms</sub> | <sub>0.2607</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>0.3021</sub> <sub>ms</sub> | <sub>0.3932</sub> <sub>ms</sub> | <sub>0.4494</sub> <sub>ms</sub> | <sub>0.3793</sub> <sub>ms</sub> | <sub>0.2384</sub> <sub>ms</sub> | <sub>0.2541</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>0.3841</sub> <sub>ms</sub> | <sub>0.4644</sub> <sub>ms</sub> | <sub>0.5102</sub> <sub>ms</sub> | <sub>0.4725</sub> <sub>ms</sub> | <sub>0.1861</sub> <sub>ms</sub> | <sub>0.2322</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>0.5674</sub> <sub>ms</sub> | <sub>0.5646</sub> <sub>ms</sub> | <sub>0.5391</sub> <sub>ms</sub> | <sub>0.5727</sub> <sub>ms</sub> | <sub>0.5050</sub> <sub>ms</sub> | <sub>0.6167</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>0.8203</sub> <sub>ms</sub> | <sub>0.8389</sub> <sub>ms</sub> | <sub>0.9030</sub> <sub>ms</sub> | <sub>0.6912</sub> <sub>ms</sub> | <sub>0.5070</sub> <sub>ms</sub> | <sub>0.6665</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>1.0736</sub> <sub>ms</sub> | <sub>1.0250</sub> <sub>ms</sub> | <sub>0.9605</sub> <sub>ms</sub> | <sub>0.8012</sub> <sub>ms</sub> | <sub>0.4753</sub> <sub>ms</sub> | <sub>0.7355</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>1.5307</sub> <sub>ms</sub> | <sub>1.1942</sub> <sub>ms</sub> | <sub>1.0357</sub> <sub>ms</sub> | <sub>0.9794</sub> <sub>ms</sub> | <sub>0.4318</sub> <sub>ms</sub> | <sub>0.7642</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>1.8394</sub> <sub>ms</sub> | <sub>1.3690</sub> <sub>ms</sub> | <sub>1.0890</sub> <sub>ms</sub> | <sub>1.1123</sub> <sub>ms</sub> | <sub>0.3820</sub> <sub>ms</sub> | <sub>0.7940</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>create_insert_sum</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.1430</sub> <sub>ms</sub> | <sub>0.1323</sub> <sub>ms</sub> | <sub>0.0198</sub> <sub>ms</sub> | <sub>0.0240</sub> <sub>ms</sub> | <sub>0.0150</sub> <sub>ms</sub> | <sub>0.0228</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.8568</sub> <sub>ms</sub> | <sub>0.7102</sub> <sub>ms</sub> | <sub>0.1077</sub> <sub>ms</sub> | <sub>0.1166</sub> <sub>ms</sub> | <sub>0.0656</sub> <sub>ms</sub> | <sub>0.1095</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.3704</sub> <sub>ms</sub> | <sub>1.3000</sub> <sub>ms</sub> | <sub>0.3507</sub> <sub>ms</sub> | <sub>0.2423</sub> <sub>ms</sub> | <sub>0.1312</sub> <sub>ms</sub> | <sub>0.2589</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.7730</sub> <sub>ms</sub> | <sub>2.5801</sub> <sub>ms</sub> | <sub>0.4272</sub> <sub>ms</sub> | <sub>0.4411</sub> <sub>ms</sub> | <sub>0.3160</sub> <sub>ms</sub> | <sub>0.5355</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.2447</sub> <sub>ms</sub> | <sub>3.9737</sub> <sub>ms</sub> | <sub>0.5863</sub> <sub>ms</sub> | <sub>0.6589</sub> <sub>ms</sub> | <sub>0.4931</sub> <sub>ms</sub> | <sub>0.8007</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.5311</sub> <sub>ms</sub> | <sub>5.6617</sub> <sub>ms</sub> | <sub>0.8538</sub> <sub>ms</sub> | <sub>0.8803</sub> <sub>ms</sub> | <sub>0.6334</sub> <sub>ms</sub> | <sub>1.0250</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>6.8923</sub> <sub>ms</sub> | <sub>6.9662</sub> <sub>ms</sub> | <sub>1.0129</sub> <sub>ms</sub> | <sub>1.3940</sub> <sub>ms</sub> | <sub>0.5516</sub> <sub>ms</sub> | <sub>0.9744</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>8.8162</sub> <sub>ms</sub> | <sub>8.2591</sub> <sub>ms</sub> | <sub>1.1718</sub> <sub>ms</sub> | <sub>1.3169</sub> <sub>ms</sub> | <sub>1.0124</sub> <sub>ms</sub> | <sub>1.5761</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>10.2962</sub> <sub>ms</sub> | <sub>10.3991</sub> <sub>ms</sub> | <sub>1.6199</sub> <sub>ms</sub> | <sub>1.5367</sub> <sub>ms</sub> | <sub>1.0477</sub> <sub>ms</sub> | <sub>1.6775</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>11.4354</sub> <sub>ms</sub> | <sub>11.0630</sub> <sub>ms</sub> | <sub>1.7916</sub> <sub>ms</sub> | <sub>1.7742</sub> <sub>ms</sub> | <sub>1.0666</sub> <sub>ms</sub> | <sub>1.8002</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>12.8154</sub> <sub>ms</sub> | <sub>13.2281</sub> <sub>ms</sub> | <sub>1.9410</sub> <sub>ms</sub> | <sub>2.0342</sub> <sub>ms</sub> | <sub>1.1037</sub> <sub>ms</sub> | <sub>1.8848</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>14.2736</sub> <sub>ms</sub> | <sub>14.8306</sub> <sub>ms</sub> | <sub>2.0815</sub> <sub>ms</sub> | <sub>2.2432</sub> <sub>ms</sub> | <sub>1.1197</sub> <sub>ms</sub> | <sub>1.9751</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>adds_and_removes</sub> <sub>sizeof(value)==8</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.9463</sub> <sub>ms</sub> | <sub>0.6998</sub> <sub>ms</sub> | <sub>0.4236</sub> <sub>ms</sub> | <sub>0.4049</sub> <sub>ms</sub> | <sub>0.3439</sub> <sub>ms</sub> | <sub>0.3474</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>4.3219</sub> <sub>ms</sub> | <sub>3.0940</sub> <sub>ms</sub> | <sub>2.1588</sub> <sub>ms</sub> | <sub>1.7971</sub> <sub>ms</sub> | <sub>1.6287</sub> <sub>ms</sub> | <sub>1.6735</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>9.4153</sub> <sub>ms</sub> | <sub>6.7733</sub> <sub>ms</sub> | <sub>4.4861</sub> <sub>ms</sub> | <sub>3.8530</sub> <sub>ms</sub> | <sub>3.4662</sub> <sub>ms</sub> | <sub>3.6696</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>23.1061</sub> <sub>ms</sub> | <sub>16.4483</sub> <sub>ms</sub> | <sub>10.9165</sub> <sub>ms</sub> | <sub>9.8012</sub> <sub>ms</sub> | <sub>8.6987</sub> <sub>ms</sub> | <sub>9.1005</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>32.9545</sub> <sub>ms</sub> | <sub>24.8782</sub> <sub>ms</sub> | <sub>14.0682</sub> <sub>ms</sub> | <sub>14.6117</sub> <sub>ms</sub> | <sub>11.7382</sub> <sub>ms</sub> | <sub>12.6037</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>50.7057</sub> <sub>ms</sub> | <sub>35.5763</sub> <sub>ms</sub> | <sub>23.7364</sub> <sub>ms</sub> | <sub>20.9827</sub> <sub>ms</sub> | <sub>18.6856</sub> <sub>ms</sub> | <sub>19.4404</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>66.0581</sub> <sub>ms</sub> | <sub>47.8714</sub> <sub>ms</sub> | <sub>30.9966</sub> <sub>ms</sub> | <sub>27.1155</sub> <sub>ms</sub> | <sub>26.6297</sub> <sub>ms</sub> | <sub>27.3350</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>84.1031</sub> <sub>ms</sub> | <sub>62.8046</sub> <sub>ms</sub> | <sub>32.4252</sub> <sub>ms</sub> | <sub>33.8475</sub> <sub>ms</sub> | <sub>26.4356</sub> <sub>ms</sub> | <sub>32.4197</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>102.6216</sub> <sub>ms</sub> | <sub>75.5629</sub> <sub>ms</sub> | <sub>43.4391</sub> <sub>ms</sub> | <sub>39.8373</sub> <sub>ms</sub> | <sub>32.3618</sub> <sub>ms</sub> | <sub>39.9326</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>154.6609</sub> <sub>ms</sub> | <sub>108.8422</sub> <sub>ms</sub> | <sub>64.2910</sub> <sub>ms</sub> | <sub>48.5983</sub> <sub>ms</sub> | <sub>41.3482</sub> <sub>ms</sub> | <sub>52.9545</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>158.0626</sub> <sub>ms</sub> | <sub>110.8120</sub> <sub>ms</sub> | <sub>71.9959</sub> <sub>ms</sub> | <sub>50.3801</sub> <sub>ms</sub> | <sub>41.9513</sub> <sub>ms</sub> | <sub>56.8670</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>215.1291</sub> <sub>ms</sub> | <sub>152.4317</sub> <sub>ms</sub> | <sub>83.6555</sub> <sub>ms</sub> | <sub>69.4553</sub> <sub>ms</sub> | <sub>57.8109</sub> <sub>ms</sub> | <sub>74.9741</sub> <sub>ms</sub> |



### log_new_big.txt
<sub>
## <sub>Timings</sub> <sub>insert_sequential</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0810</sub> <sub>ms</sub> | <sub>0.0638</sub> <sub>ms</sub> | <sub>0.0878</sub> <sub>ms</sub> | <sub>0.0307</sub> <sub>ms</sub> | <sub>0.0158</sub> <sub>ms</sub> | <sub>0.0190</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4089</sub> <sub>ms</sub> | <sub>0.3216</sub> <sub>ms</sub> | <sub>0.7457</sub> <sub>ms</sub> | <sub>0.1449</sub> <sub>ms</sub> | <sub>0.0793</sub> <sub>ms</sub> | <sub>0.1085</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.8737</sub> <sub>ms</sub> | <sub>0.6908</sub> <sub>ms</sub> | <sub>2.5693</sub> <sub>ms</sub> | <sub>0.2900</sub> <sub>ms</sub> | <sub>0.1654</sub> <sub>ms</sub> | <sub>0.1814</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>1.8600</sub> <sub>ms</sub> | <sub>1.5175</sub> <sub>ms</sub> | <sub>6.5821</sub> <sub>ms</sub> | <sub>0.5815</sub> <sub>ms</sub> | <sub>0.3622</sub> <sub>ms</sub> | <sub>0.3960</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>2.8644</sub> <sub>ms</sub> | <sub>2.3514</sub> <sub>ms</sub> | <sub>6.5649</sub> <sub>ms</sub> | <sub>0.8797</sub> <sub>ms</sub> | <sub>0.6408</sub> <sub>ms</sub> | <sub>0.6485</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>3.9080</sub> <sub>ms</sub> | <sub>3.2525</sub> <sub>ms</sub> | <sub>13.5583</sub> <sub>ms</sub> | <sub>1.1769</sub> <sub>ms</sub> | <sub>0.8931</sub> <sub>ms</sub> | <sub>0.8773</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>5.0843</sub> <sub>ms</sub> | <sub>4.2435</sub> <sub>ms</sub> | <sub>13.8011</sub> <sub>ms</sub> | <sub>1.4814</sub> <sub>ms</sub> | <sub>1.0860</sub> <sub>ms</sub> | <sub>1.0973</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>6.4704</sub> <sub>ms</sub> | <sub>5.5651</sub> <sub>ms</sub> | <sub>14.1408</sub> <sub>ms</sub> | <sub>2.1708</sub> <sub>ms</sub> | <sub>1.3280</sub> <sub>ms</sub> | <sub>1.3518</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>7.9667</sub> <sub>ms</sub> | <sub>6.6674</sub> <sub>ms</sub> | <sub>27.3693</sub> <sub>ms</sub> | <sub>2.0982</sub> <sub>ms</sub> | <sub>1.5257</sub> <sub>ms</sub> | <sub>1.5600</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>9.3738</sub> <sub>ms</sub> | <sub>7.8651</sub> <sub>ms</sub> | <sub>27.7641</sub> <sub>ms</sub> | <sub>2.4075</sub> <sub>ms</sub> | <sub>1.7441</sub> <sub>ms</sub> | <sub>1.7924</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>10.8420</sub> <sub>ms</sub> | <sub>9.2659</sub> <sub>ms</sub> | <sub>27.9747</sub> <sub>ms</sub> | <sub>2.7055</sub> <sub>ms</sub> | <sub>1.9518</sub> <sub>ms</sub> | <sub>2.0139</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>11.9455</sub> <sub>ms</sub> | <sub>10.4830</sub> <sub>ms</sub> | <sub>29.0707</sub> <sub>ms</sub> | <sub>2.9969</sub> <sub>ms</sub> | <sub>2.1144</sub> <sub>ms</sub> | <sub>2.2412</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>insert_random</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0930</sub> <sub>ms</sub> | <sub>0.0708</sub> <sub>ms</sub> | <sub>0.1020</sub> <sub>ms</sub> | <sub>0.0361</sub> <sub>ms</sub> | <sub>0.0225</sub> <sub>ms</sub> | <sub>0.0281</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.5122</sub> <sub>ms</sub> | <sub>0.4078</sub> <sub>ms</sub> | <sub>0.9340</sub> <sub>ms</sub> | <sub>0.1815</sub> <sub>ms</sub> | <sub>0.1770</sub> <sub>ms</sub> | <sub>0.1364</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.1113</sub> <sub>ms</sub> | <sub>0.8278</sub> <sub>ms</sub> | <sub>3.3159</sub> <sub>ms</sub> | <sub>0.3714</sub> <sub>ms</sub> | <sub>0.3766</sub> <sub>ms</sub> | <sub>0.2909</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.4416</sub> <sub>ms</sub> | <sub>1.9306</sub> <sub>ms</sub> | <sub>8.0283</sub> <sub>ms</sub> | <sub>0.7826</sub> <sub>ms</sub> | <sub>0.8939</sub> <sub>ms</sub> | <sub>0.6323</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.0886</sub> <sub>ms</sub> | <sub>3.4145</sub> <sub>ms</sub> | <sub>9.0062</sub> <sub>ms</sub> | <sub>1.6848</sub> <sub>ms</sub> | <sub>1.7527</sub> <sub>ms</sub> | <sub>0.9843</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.8777</sub> <sub>ms</sub> | <sub>4.9659</sub> <sub>ms</sub> | <sub>17.7198</sub> <sub>ms</sub> | <sub>2.2568</sub> <sub>ms</sub> | <sub>3.0321</sub> <sub>ms</sub> | <sub>1.4466</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>8.8504</sub> <sub>ms</sub> | <sub>6.8701</sub> <sub>ms</sub> | <sub>18.7098</sub> <sub>ms</sub> | <sub>2.8568</sub> <sub>ms</sub> | <sub>4.7850</sub> <sub>ms</sub> | <sub>2.0037</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>11.2610</sub> <sub>ms</sub> | <sub>8.9925</sub> <sub>ms</sub> | <sub>19.9614</sub> <sub>ms</sub> | <sub>3.7974</sub> <sub>ms</sub> | <sub>4.5527</sub> <sub>ms</sub> | <sub>3.0226</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>14.0390</sub> <sub>ms</sub> | <sub>11.2492</sub> <sub>ms</sub> | <sub>35.7341</sub> <sub>ms</sub> | <sub>4.4633</sub> <sub>ms</sub> | <sub>5.8308</sub> <sub>ms</sub> | <sub>3.6638</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>17.1178</sub> <sub>ms</sub> | <sub>13.1006</sub> <sub>ms</sub> | <sub>36.9813</sub> <sub>ms</sub> | <sub>5.3363</sub> <sub>ms</sub> | <sub>7.3168</sub> <sub>ms</sub> | <sub>4.1710</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>20.0737</sub> <sub>ms</sub> | <sub>16.0421</sub> <sub>ms</sub> | <sub>38.2084</sub> <sub>ms</sub> | <sub>6.1367</sub> <sub>ms</sub> | <sub>9.2290</sub> <sub>ms</sub> | <sub>4.9027</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>23.4549</sub> <sub>ms</sub> | <sub>18.2801</sub> <sub>ms</sub> | <sub>39.5513</sub> <sub>ms</sub> | <sub>7.3277</sub> <sub>ms</sub> | <sub>11.7744</sub> <sub>ms</sub> | <sub>5.4911</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_sequential</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0179</sub> <sub>ms</sub> | <sub>0.0112</sub> <sub>ms</sub> | <sub>0.0076</sub> <sub>ms</sub> | <sub>0.0097</sub> <sub>ms</sub> | <sub>0.0018</sub> <sub>ms</sub> | <sub>0.0033</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0900</sub> <sub>ms</sub> | <sub>0.0562</sub> <sub>ms</sub> | <sub>0.0470</sub> <sub>ms</sub> | <sub>0.0465</sub> <sub>ms</sub> | <sub>0.0137</sub> <sub>ms</sub> | <sub>0.0151</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.1803</sub> <sub>ms</sub> | <sub>0.1234</sub> <sub>ms</sub> | <sub>0.0821</sub> <sub>ms</sub> | <sub>0.0994</sub> <sub>ms</sub> | <sub>0.0273</sub> <sub>ms</sub> | <sub>0.0368</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.3951</sub> <sub>ms</sub> | <sub>0.2981</sub> <sub>ms</sub> | <sub>0.2454</sub> <sub>ms</sub> | <sub>0.2530</sub> <sub>ms</sub> | <sub>0.1217</sub> <sub>ms</sub> | <sub>0.1727</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.6468</sub> <sub>ms</sub> | <sub>0.4845</sub> <sub>ms</sub> | <sub>0.3708</sub> <sub>ms</sub> | <sub>0.4351</sub> <sub>ms</sub> | <sub>0.2237</sub> <sub>ms</sub> | <sub>0.4112</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>0.8856</sub> <sub>ms</sub> | <sub>0.6868</sub> <sub>ms</sub> | <sub>0.5260</sub> <sub>ms</sub> | <sub>0.5965</sub> <sub>ms</sub> | <sub>0.3004</sub> <sub>ms</sub> | <sub>0.3681</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>1.1313</sub> <sub>ms</sub> | <sub>0.8484</sub> <sub>ms</sub> | <sub>0.6709</sub> <sub>ms</sub> | <sub>0.7630</sub> <sub>ms</sub> | <sub>0.3817</sub> <sub>ms</sub> | <sub>0.4321</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>1.3716</sub> <sub>ms</sub> | <sub>1.0236</sub> <sub>ms</sub> | <sub>0.9412</sub> <sub>ms</sub> | <sub>0.9362</sub> <sub>ms</sub> | <sub>0.4804</sub> <sub>ms</sub> | <sub>0.5594</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>1.7100</sub> <sub>ms</sub> | <sub>1.1632</sub> <sub>ms</sub> | <sub>1.0186</sub> <sub>ms</sub> | <sub>1.0987</sub> <sub>ms</sub> | <sub>0.5641</sub> <sub>ms</sub> | <sub>0.6538</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>1.8237</sub> <sub>ms</sub> | <sub>1.3470</sub> <sub>ms</sub> | <sub>1.1166</sub> <sub>ms</sub> | <sub>1.4300</sub> <sub>ms</sub> | <sub>0.6549</sub> <sub>ms</sub> | <sub>0.7873</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>2.1249</sub> <sub>ms</sub> | <sub>1.5252</sub> <sub>ms</sub> | <sub>1.3085</sub> <sub>ms</sub> | <sub>1.4611</sub> <sub>ms</sub> | <sub>0.7438</sub> <sub>ms</sub> | <sub>0.8645</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>2.3311</sub> <sub>ms</sub> | <sub>1.7340</sub> <sub>ms</sub> | <sub>1.3906</sub> <sub>ms</sub> | <sub>1.6226</sub> <sub>ms</sub> | <sub>0.8408</sub> <sub>ms</sub> | <sub>0.9688</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>get_random</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0271</sub> <sub>ms</sub> | <sub>0.0166</sub> <sub>ms</sub> | <sub>0.0124</sub> <sub>ms</sub> | <sub>0.0149</sub> <sub>ms</sub> | <sub>0.0068</sub> <sub>ms</sub> | <sub>0.0074</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.1652</sub> <sub>ms</sub> | <sub>0.1227</sub> <sub>ms</sub> | <sub>0.0635</sub> <sub>ms</sub> | <sub>0.0886</sub> <sub>ms</sub> | <sub>0.0591</sub> <sub>ms</sub> | <sub>0.0611</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.3525</sub> <sub>ms</sub> | <sub>0.2117</sub> <sub>ms</sub> | <sub>0.1624</sub> <sub>ms</sub> | <sub>0.1904</sub> <sub>ms</sub> | <sub>0.1286</sub> <sub>ms</sub> | <sub>0.1099</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.9704</sub> <sub>ms</sub> | <sub>0.6578</sub> <sub>ms</sub> | <sub>0.6050</sub> <sub>ms</sub> | <sub>0.5187</sub> <sub>ms</sub> | <sub>0.3272</sub> <sub>ms</sub> | <sub>0.2800</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>1.9573</sub> <sub>ms</sub> | <sub>1.4266</sub> <sub>ms</sub> | <sub>0.9744</sub> <sub>ms</sub> | <sub>0.8960</sub> <sub>ms</sub> | <sub>0.4427</sub> <sub>ms</sub> | <sub>0.5004</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>3.0865</sub> <sub>ms</sub> | <sub>2.2212</sub> <sub>ms</sub> | <sub>1.4552</sub> <sub>ms</sub> | <sub>1.3588</sub> <sub>ms</sub> | <sub>1.0756</sub> <sub>ms</sub> | <sub>0.7717</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>4.7812</sub> <sub>ms</sub> | <sub>3.1332</sub> <sub>ms</sub> | <sub>2.0010</sub> <sub>ms</sub> | <sub>1.9827</sub> <sub>ms</sub> | <sub>2.2709</sub> <sub>ms</sub> | <sub>1.1406</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>6.1768</sub> <sub>ms</sub> | <sub>4.1070</sub> <sub>ms</sub> | <sub>2.6146</sub> <sub>ms</sub> | <sub>2.6131</sub> <sub>ms</sub> | <sub>1.2671</sub> <sub>ms</sub> | <sub>1.3690</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>7.5662</sub> <sub>ms</sub> | <sub>4.8115</sub> <sub>ms</sub> | <sub>2.7621</sub> <sub>ms</sub> | <sub>3.1798</sub> <sub>ms</sub> | <sub>1.7656</sub> <sub>ms</sub> | <sub>1.6074</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>9.1209</sub> <sub>ms</sub> | <sub>5.9433</sub> <sub>ms</sub> | <sub>3.2201</sub> <sub>ms</sub> | <sub>3.7568</sub> <sub>ms</sub> | <sub>2.7262</sub> <sub>ms</sub> | <sub>1.9713</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>10.7859</sub> <sub>ms</sub> | <sub>6.8709</sub> <sub>ms</sub> | <sub>3.9510</sub> <sub>ms</sub> | <sub>4.4172</sub> <sub>ms</sub> | <sub>4.5935</sub> <sub>ms</sub> | <sub>2.3322</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>12.7336</sub> <sub>ms</sub> | <sub>8.2587</sub> <sub>ms</sub> | <sub>4.5234</sub> <sub>ms</sub> | <sub>5.0049</sub> <sub>ms</sub> | <sub>6.3764</sub> <sub>ms</sub> | <sub>3.0592</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_sequential</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.1172</sub> <sub>ms</sub> | <sub>0.0842</sub> <sub>ms</sub> | <sub>0.0087</sub> <sub>ms</sub> | <sub>0.0109</sub> <sub>ms</sub> | <sub>0.0054</sub> <sub>ms</sub> | <sub>0.0096</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4724</sub> <sub>ms</sub> | <sub>0.3407</sub> <sub>ms</sub> | <sub>0.0434</sub> <sub>ms</sub> | <sub>0.0549</sub> <sub>ms</sub> | <sub>0.0317</sub> <sub>ms</sub> | <sub>0.0447</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.9943</sub> <sub>ms</sub> | <sub>0.6810</sub> <sub>ms</sub> | <sub>0.1126</sub> <sub>ms</sub> | <sub>0.1104</sub> <sub>ms</sub> | <sub>0.0659</sub> <sub>ms</sub> | <sub>0.0890</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.3804</sub> <sub>ms</sub> | <sub>1.8509</sub> <sub>ms</sub> | <sub>0.3300</sub> <sub>ms</sub> | <sub>0.2525</sub> <sub>ms</sub> | <sub>0.2494</sub> <sub>ms</sub> | <sub>0.2210</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.3447</sub> <sub>ms</sub> | <sub>3.5608</sub> <sub>ms</sub> | <sub>0.5293</sub> <sub>ms</sub> | <sub>0.5873</sub> <sub>ms</sub> | <sub>0.4513</sub> <sub>ms</sub> | <sub>0.4525</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.3634</sub> <sub>ms</sub> | <sub>5.2178</sub> <sub>ms</sub> | <sub>0.7626</sub> <sub>ms</sub> | <sub>0.8485</sub> <sub>ms</sub> | <sub>0.6596</sub> <sub>ms</sub> | <sub>0.5508</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>6.7318</sub> <sub>ms</sub> | <sub>5.7730</sub> <sub>ms</sub> | <sub>0.9964</sub> <sub>ms</sub> | <sub>1.0469</sub> <sub>ms</sub> | <sub>0.8520</sub> <sub>ms</sub> | <sub>0.7005</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>8.2061</sub> <sub>ms</sub> | <sub>7.3192</sub> <sub>ms</sub> | <sub>1.2146</sub> <sub>ms</sub> | <sub>1.2707</sub> <sub>ms</sub> | <sub>1.1346</sub> <sub>ms</sub> | <sub>0.8433</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>9.3882</sub> <sub>ms</sub> | <sub>8.2616</sub> <sub>ms</sub> | <sub>1.4318</sub> <sub>ms</sub> | <sub>1.4700</sub> <sub>ms</sub> | <sub>1.2472</sub> <sub>ms</sub> | <sub>0.9971</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>11.3548</sub> <sub>ms</sub> | <sub>9.1237</sub> <sub>ms</sub> | <sub>1.6633</sub> <sub>ms</sub> | <sub>1.6969</sub> <sub>ms</sub> | <sub>1.4457</sub> <sub>ms</sub> | <sub>1.1530</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>11.5883</sub> <sub>ms</sub> | <sub>10.0558</sub> <sub>ms</sub> | <sub>2.1865</sub> <sub>ms</sub> | <sub>1.9321</sub> <sub>ms</sub> | <sub>1.6508</sub> <sub>ms</sub> | <sub>1.3206</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>12.6114</sub> <sub>ms</sub> | <sub>11.3835</sub> <sub>ms</sub> | <sub>2.4057</sub> <sub>ms</sub> | <sub>2.1539</sub> <sub>ms</sub> | <sub>1.9597</sub> <sub>ms</sub> | <sub>1.6345</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>erase_random</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.1536</sub> <sub>ms</sub> | <sub>0.1014</sub> <sub>ms</sub> | <sub>0.0135</sub> <sub>ms</sub> | <sub>0.0140</sub> <sub>ms</sub> | <sub>0.0157</sub> <sub>ms</sub> | <sub>0.0155</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.6778</sub> <sub>ms</sub> | <sub>0.4410</sub> <sub>ms</sub> | <sub>0.0777</sub> <sub>ms</sub> | <sub>0.0801</sub> <sub>ms</sub> | <sub>0.1162</sub> <sub>ms</sub> | <sub>0.0897</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.7809</sub> <sub>ms</sub> | <sub>1.2713</sub> <sub>ms</sub> | <sub>0.1649</sub> <sub>ms</sub> | <sub>0.1702</sub> <sub>ms</sub> | <sub>0.2437</sub> <sub>ms</sub> | <sub>0.1882</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>4.5999</sub> <sub>ms</sub> | <sub>3.4197</sub> <sub>ms</sub> | <sub>0.6312</sub> <sub>ms</sub> | <sub>0.5061</sub> <sub>ms</sub> | <sub>0.6475</sub> <sub>ms</sub> | <sub>0.4089</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>8.5665</sub> <sub>ms</sub> | <sub>6.5352</sub> <sub>ms</sub> | <sub>1.1441</sub> <sub>ms</sub> | <sub>0.8971</sub> <sub>ms</sub> | <sub>1.1177</sub> <sub>ms</sub> | <sub>0.6911</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>13.4990</sub> <sub>ms</sub> | <sub>10.3417</sub> <sub>ms</sub> | <sub>1.4687</sub> <sub>ms</sub> | <sub>1.4015</sub> <sub>ms</sub> | <sub>2.1463</sub> <sub>ms</sub> | <sub>0.9930</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>17.5973</sub> <sub>ms</sub> | <sub>13.7663</sub> <sub>ms</sub> | <sub>2.0093</sub> <sub>ms</sub> | <sub>1.9913</sub> <sub>ms</sub> | <sub>3.4949</sub> <sub>ms</sub> | <sub>1.3897</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>23.9133</sub> <sub>ms</sub> | <sub>17.9693</sub> <sub>ms</sub> | <sub>2.8970</sub> <sub>ms</sub> | <sub>2.7105</sub> <sub>ms</sub> | <sub>2.9836</sub> <sub>ms</sub> | <sub>2.2750</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>29.2711</sub> <sub>ms</sub> | <sub>22.7289</sub> <sub>ms</sub> | <sub>3.0607</sub> <sub>ms</sub> | <sub>3.2960</sub> <sub>ms</sub> | <sub>3.9205</sub> <sub>ms</sub> | <sub>2.6438</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>36.2907</sub> <sub>ms</sub> | <sub>26.4846</sub> <sub>ms</sub> | <sub>3.8128</sub> <sub>ms</sub> | <sub>3.9992</sub> <sub>ms</sub> | <sub>4.9668</sub> <sub>ms</sub> | <sub>2.9868</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>42.3046</sub> <sub>ms</sub> | <sub>31.1127</sub> <sub>ms</sub> | <sub>4.3427</sub> <sub>ms</sub> | <sub>4.6900</sub> <sub>ms</sub> | <sub>6.3451</sub> <sub>ms</sub> | <sub>3.4248</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>50.1609</sub> <sub>ms</sub> | <sub>34.3392</sub> <sub>ms</sub> | <sub>5.0846</sub> <sub>ms</sub> | <sub>5.4283</sub> <sub>ms</sub> | <sub>8.2787</sub> <sub>ms</sub> | <sub>3.8985</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>iterator</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.0042</sub> <sub>ms</sub> | <sub>0.0077</sub> <sub>ms</sub> | <sub>0.0088</sub> <sub>ms</sub> | <sub>0.0067</sub> <sub>ms</sub> | <sub>0.0041</sub> <sub>ms</sub> | <sub>0.0035</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0428</sub> <sub>ms</sub> | <sub>0.0491</sub> <sub>ms</sub> | <sub>0.0684</sub> <sub>ms</sub> | <sub>0.0469</sub> <sub>ms</sub> | <sub>0.0374</sub> <sub>ms</sub> | <sub>0.0382</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.0945</sub> <sub>ms</sub> | <sub>0.0981</sub> <sub>ms</sub> | <sub>0.2093</sub> <sub>ms</sub> | <sub>0.0973</sub> <sub>ms</sub> | <sub>0.0953</sub> <sub>ms</sub> | <sub>0.0716</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.2711</sub> <sub>ms</sub> | <sub>0.2352</sub> <sub>ms</sub> | <sub>0.5501</sub> <sub>ms</sub> | <sub>0.2240</sub> <sub>ms</sub> | <sub>0.2981</sub> <sub>ms</sub> | <sub>0.2075</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.7536</sub> <sub>ms</sub> | <sub>0.4076</sub> <sub>ms</sub> | <sub>0.6433</sub> <sub>ms</sub> | <sub>0.4131</sub> <sub>ms</sub> | <sub>0.7089</sub> <sub>ms</sub> | <sub>0.4558</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>1.5084</sub> <sub>ms</sub> | <sub>0.6537</sub> <sub>ms</sub> | <sub>1.2886</sub> <sub>ms</sub> | <sub>0.6535</sub> <sub>ms</sub> | <sub>0.7155</sub> <sub>ms</sub> | <sub>0.5691</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>2.1249</sub> <sub>ms</sub> | <sub>0.9290</sub> <sub>ms</sub> | <sub>1.3211</sub> <sub>ms</sub> | <sub>0.8892</sub> <sub>ms</sub> | <sub>0.6874</sub> <sub>ms</sub> | <sub>0.6657</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>2.8286</sub> <sub>ms</sub> | <sub>1.1458</sub> <sub>ms</sub> | <sub>1.3386</sub> <sub>ms</sub> | <sub>1.1351</sub> <sub>ms</sub> | <sub>1.2297</sub> <sub>ms</sub> | <sub>1.0574</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>3.4457</sub> <sub>ms</sub> | <sub>1.3647</sub> <sub>ms</sub> | <sub>2.2974</sub> <sub>ms</sub> | <sub>1.3838</sub> <sub>ms</sub> | <sub>1.3685</sub> <sub>ms</sub> | <sub>1.1625</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>4.0941</sub> <sub>ms</sub> | <sub>1.5590</sub> <sub>ms</sub> | <sub>2.3257</sub> <sub>ms</sub> | <sub>1.5897</sub> <sub>ms</sub> | <sub>1.2903</sub> <sub>ms</sub> | <sub>1.2553</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>4.7314</sub> <sub>ms</sub> | <sub>1.7576</sub> <sub>ms</sub> | <sub>2.4042</sub> <sub>ms</sub> | <sub>1.8161</sub> <sub>ms</sub> | <sub>1.2435</sub> <sub>ms</sub> | <sub>1.3495</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>5.3590</sub> <sub>ms</sub> | <sub>2.0162</sub> <sub>ms</sub> | <sub>2.4330</sub> <sub>ms</sub> | <sub>2.0176</sub> <sub>ms</sub> | <sub>1.2618</sub> <sub>ms</sub> | <sub>1.5118</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>create_insert_sum</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>0.1694</sub> <sub>ms</sub> | <sub>0.1588</sub> <sub>ms</sub> | <sub>0.0544</sub> <sub>ms</sub> | <sub>0.0318</sub> <sub>ms</sub> | <sub>0.1213</sub> <sub>ms</sub> | <sub>0.0824</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.7904</sub> <sub>ms</sub> | <sub>0.7249</sub> <sub>ms</sub> | <sub>0.3590</sub> <sub>ms</sub> | <sub>0.1597</sub> <sub>ms</sub> | <sub>0.5369</sub> <sub>ms</sub> | <sub>0.4208</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.6565</sub> <sub>ms</sub> | <sub>1.7679</sub> <sub>ms</sub> | <sub>1.8820</sub> <sub>ms</sub> | <sub>0.3178</sub> <sub>ms</sub> | <sub>1.2009</sub> <sub>ms</sub> | <sub>0.8271</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>3.7836</sub> <sub>ms</sub> | <sub>3.7148</sub> <sub>ms</sub> | <sub>4.1886</sub> <sub>ms</sub> | <sub>0.6445</sub> <sub>ms</sub> | <sub>2.4721</sub> <sub>ms</sub> | <sub>1.8713</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>6.6171</sub> <sub>ms</sub> | <sub>6.6268</sub> <sub>ms</sub> | <sub>4.6224</sub> <sub>ms</sub> | <sub>1.9246</sub> <sub>ms</sub> | <sub>4.9394</sub> <sub>ms</sub> | <sub>2.9168</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>9.1034</sub> <sub>ms</sub> | <sub>9.3453</sub> <sub>ms</sub> | <sub>8.1057</sub> <sub>ms</sub> | <sub>2.6973</sub> <sub>ms</sub> | <sub>5.1246</sub> <sub>ms</sub> | <sub>3.7488</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>10.9468</sub> <sub>ms</sub> | <sub>10.8583</sub> <sub>ms</sub> | <sub>8.4098</sub> <sub>ms</sub> | <sub>3.5018</sub> <sub>ms</sub> | <sub>5.4444</sub> <sub>ms</sub> | <sub>4.5699</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>15.1151</sub> <sub>ms</sub> | <sub>14.1095</sub> <sub>ms</sub> | <sub>8.8345</sub> <sub>ms</sub> | <sub>4.1378</sub> <sub>ms</sub> | <sub>16.5147</sub> <sub>ms</sub> | <sub>6.1533</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>19.1160</sub> <sub>ms</sub> | <sub>17.4279</sub> <sub>ms</sub> | <sub>16.1229</sub> <sub>ms</sub> | <sub>4.8549</sub> <sub>ms</sub> | <sub>17.3132</sub> <sub>ms</sub> | <sub>6.8544</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>21.0504</sub> <sub>ms</sub> | <sub>19.8791</sub> <sub>ms</sub> | <sub>16.3304</sub> <sub>ms</sub> | <sub>5.6281</sub> <sub>ms</sub> | <sub>9.9926</sub> <sub>ms</sub> | <sub>7.4684</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>24.1514</sub> <sub>ms</sub> | <sub>22.6030</sub> <sub>ms</sub> | <sub>16.9760</sub> <sub>ms</sub> | <sub>6.2466</sub> <sub>ms</sub> | <sub>10.5229</sub> <sub>ms</sub> | <sub>8.3919</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>26.9918</sub> <sub>ms</sub> | <sub>25.2682</sub> <sub>ms</sub> | <sub>16.8530</sub> <sub>ms</sub> | <sub>7.1673</sub> <sub>ms</sub> | <sub>10.3205</sub> <sub>ms</sub> | <sub>9.3534</sub> <sub>ms</sub> |


## <sub>Timings</sub> <sub>adds_and_removes</sub> <sub>sizeof(value)==152</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>dmHashTable</sub> | <sub>jc::hashtable</sub> | <sub>jc::hashtable2</sub> |
|-------:|--------------------|-----------------|------------------------|-------------|---------------|----------------|
| <sub>1000</sub> | <sub>1.0369</sub> <sub>ms</sub> | <sub>0.7884</sub> <sub>ms</sub> | <sub>0.5574</sub> <sub>ms</sub> | <sub>0.5173</sub> <sub>ms</sub> | <sub>0.4666</sub> <sub>ms</sub> | <sub>0.5207</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>5.0466</sub> <sub>ms</sub> | <sub>3.7531</sub> <sub>ms</sub> | <sub>3.6713</sub> <sub>ms</sub> | <sub>2.3867</sub> <sub>ms</sub> | <sub>2.3970</sub> <sub>ms</sub> | <sub>2.3553</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>10.9520</sub> <sub>ms</sub> | <sub>8.0527</sub> <sub>ms</sub> | <sub>13.1174</sub> <sub>ms</sub> | <sub>5.1883</sub> <sub>ms</sub> | <sub>5.2334</sub> <sub>ms</sub> | <sub>5.0838</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>27.7807</sub> <sub>ms</sub> | <sub>20.5394</sub> <sub>ms</sub> | <sub>43.6088</sub> <sub>ms</sub> | <sub>13.2581</sub> <sub>ms</sub> | <sub>13.8067</sub> <sub>ms</sub> | <sub>12.5417</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>47.1791</sub> <sub>ms</sub> | <sub>35.7249</sub> <sub>ms</sub> | <sub>25.7926</sub> <sub>ms</sub> | <sub>21.8532</sub> <sub>ms</sub> | <sub>24.7785</sub> <sub>ms</sub> | <sub>21.6677</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>87.8004</sub> <sub>ms</sub> | <sub>61.3213</sub> <sub>ms</sub> | <sub>89.3510</sub> <sub>ms</sub> | <sub>38.7317</sub> <sub>ms</sub> | <sub>42.5278</sub> <sub>ms</sub> | <sub>30.4085</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>131.8197</sub> <sub>ms</sub> | <sub>94.4691</sub> <sub>ms</sub> | <sub>113.5045</sub> <sub>ms</sub> | <sub>55.5640</sub> <sub>ms</sub> | <sub>64.2727</sub> <sub>ms</sub> | <sub>39.6750</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>176.1852</sub> <sub>ms</sub> | <sub>122.8516</sub> <sub>ms</sub> | <sub>74.4383</sub> <sub>ms</sub> | <sub>69.7673</sub> <sub>ms</sub> | <sub>69.6754</sub> <sub>ms</sub> | <sub>63.6827</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>216.3200</sub> <sub>ms</sub> | <sub>149.1478</sub> <sub>ms</sub> | <sub>135.2979</sub> <sub>ms</sub> | <sub>88.6502</sub> <sub>ms</sub> | <sub>85.6358</sub> <sub>ms</sub> | <sub>66.9997</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>282.8951</sub> <sub>ms</sub> | <sub>200.4925</sub> <sub>ms</sub> | <sub>221.4451</sub> <sub>ms</sub> | <sub>121.3509</sub> <sub>ms</sub> | <sub>119.5793</sub> <sub>ms</sub> | <sub>85.9353</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>289.1563</sub> <sub>ms</sub> | <sub>204.4107</sub> <sub>ms</sub> | <sub>264.6564</sub> <sub>ms</sub> | <sub>116.7427</sub> <sub>ms</sub> | <sub>116.8000</sub> <sub>ms</sub> | <sub>85.2769</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>402.0028</sub> <sub>ms</sub> | <sub>275.9387</sub> <sub>ms</sub> | <sub>251.0267</sub> <sub>ms</sub> | <sub>149.9025</sub> <sub>ms</sub> | <sub>166.0448</sub> <sub>ms</sub> | <sub>117.8925</sub> <sub>ms</sub> |


