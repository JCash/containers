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
<sub>##</sub> <sub>Timings</sub> <sub>insert_sequential</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0911</sub> <sub>ms</sub> | <sub>0.0914</sub> <sub>ms</sub> | <sub>0.0880</sub> <sub>ms</sub> | <sub>0.0269</sub> <sub>ms</sub> | <sub>0.0024</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.4313</sub> <sub>ms</sub> | <sub>0.3969</sub> <sub>ms</sub> | <sub>0.3359</sub> <sub>ms</sub> | <sub>0.1608</sub> <sub>ms</sub> | <sub>0.0119</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.8537</sub> <sub>ms</sub> | <sub>0.7948</sub> <sub>ms</sub> | <sub>0.6755</sub> <sub>ms</sub> | <sub>0.2752</sub> <sub>ms</sub> | <sub>0.0224</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>1.7101</sub> <sub>ms</sub> | <sub>1.6056</sub> <sub>ms</sub> | <sub>1.3563</sub> <sub>ms</sub> | <sub>0.5952</sub> <sub>ms</sub> | <sub>0.0489</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>2.7124</sub> <sub>ms</sub> | <sub>2.5198</sub> <sub>ms</sub> | <sub>1.8987</sub> <sub>ms</sub> | <sub>0.6962</sub> <sub>ms</sub> | <sub>0.0673</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>3.4682</sub> <sub>ms</sub> | <sub>3.2516</sub> <sub>ms</sub> | <sub>2.8356</sub> <sub>ms</sub> | <sub>1.1602</sub> <sub>ms</sub> | <sub>0.0977</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>4.2686</sub> <sub>ms</sub> | <sub>4.4724</sub> <sub>ms</sub> | <sub>3.3971</sub> <sub>ms</sub> | <sub>1.3210</sub> <sub>ms</sub> | <sub>0.1121</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>5.5923</sub> <sub>ms</sub> | <sub>5.1193</sub> <sub>ms</sub> | <sub>3.9619</sub> <sub>ms</sub> | <sub>1.4392</sub> <sub>ms</sub> | <sub>0.1345</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>6.3390</sub> <sub>ms</sub> | <sub>5.9599</sub> <sub>ms</sub> | <sub>5.2843</sub> <sub>ms</sub> | <sub>2.4889</sub> <sub>ms</sub> | <sub>0.1571</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>7.0612</sub> <sub>ms</sub> | <sub>6.7637</sub> <sub>ms</sub> | <sub>5.9741</sub> <sub>ms</sub> | <sub>2.6404</sub> <sub>ms</sub> | <sub>0.1794</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>7.9096</sub> <sub>ms</sub> | <sub>7.4041</sub> <sub>ms</sub> | <sub>6.4550</sub> <sub>ms</sub> | <sub>2.8086</sub> <sub>ms</sub> | <sub>0.2018</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>8.7586</sub> <sub>ms</sub> | <sub>9.2398</sub> <sub>ms</sub> | <sub>7.0148</sub> <sub>ms</sub> | <sub>2.9692</sub> <sub>ms</sub> | <sub>0.2245</sub> <sub>ms</sub> |


<sub>##</sub> <sub>Timings</sub> <sub>insert_random</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1226</sub> <sub>ms</sub> | <sub>0.1156</sub> <sub>ms</sub> | <sub>0.0944</sub> <sub>ms</sub> | <sub>0.0425</sub> <sub>ms</sub> | <sub>0.0101</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.6624</sub> <sub>ms</sub> | <sub>0.5227</sub> <sub>ms</sub> | <sub>0.4602</sub> <sub>ms</sub> | <sub>0.2523</sub> <sub>ms</sub> | <sub>0.0749</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.2309</sub> <sub>ms</sub> | <sub>1.0573</sub> <sub>ms</sub> | <sub>0.9358</sub> <sub>ms</sub> | <sub>0.5095</sub> <sub>ms</sub> | <sub>0.1505</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.5461</sub> <sub>ms</sub> | <sub>2.2666</sub> <sub>ms</sub> | <sub>1.9491</sub> <sub>ms</sub> | <sub>1.0327</sub> <sub>ms</sub> | <sub>0.3628</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.1463</sub> <sub>ms</sub> | <sub>3.6921</sub> <sub>ms</sub> | <sub>2.7542</sub> <sub>ms</sub> | <sub>1.3309</sub> <sub>ms</sub> | <sub>1.2404</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.3609</sub> <sub>ms</sub> | <sub>4.8067</sub> <sub>ms</sub> | <sub>4.1350</sub> <sub>ms</sub> | <sub>2.1969</sub> <sub>ms</sub> | <sub>0.7045</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>6.5768</sub> <sub>ms</sub> | <sub>6.7427</sub> <sub>ms</sub> | <sub>4.9438</sub> <sub>ms</sub> | <sub>2.5015</sub> <sub>ms</sub> | <sub>1.1614</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>9.1941</sub> <sub>ms</sub> | <sub>8.2169</sub> <sub>ms</sub> | <sub>5.7917</sub> <sub>ms</sub> | <sub>2.8805</sub> <sub>ms</sub> | <sub>2.5893</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>10.1365</sub> <sub>ms</sub> | <sub>8.8176</sub> <sub>ms</sub> | <sub>8.4188</sub> <sub>ms</sub> | <sub>5.2097</sub> <sub>ms</sub> | <sub>1.1229</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>12.1436</sub> <sub>ms</sub> | <sub>10.3555</sub> <sub>ms</sub> | <sub>9.4640</sub> <sub>ms</sub> | <sub>5.4117</sub> <sub>ms</sub> | <sub>1.4487</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>13.7588</sub> <sub>ms</sub> | <sub>12.3867</sub> <sub>ms</sub> | <sub>10.4999</sub> <sub>ms</sub> | <sub>5.9058</sub> <sub>ms</sub> | <sub>1.8458</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>14.5588</sub> <sub>ms</sub> | <sub>17.1879</sub> <sub>ms</sub> | <sub>11.4229</sub> <sub>ms</sub> | <sub>6.6065</sub> <sub>ms</sub> | <sub>2.3743</sub> <sub>ms</sub> |


<sub>##</sub> <sub>Timings</sub> <sub>get_sequential</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0174</sub> <sub>ms</sub> | <sub>0.0134</sub> <sub>ms</sub> | <sub>0.0122</sub> <sub>ms</sub> | <sub>0.0084</sub> <sub>ms</sub> | <sub>0.0013</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0878</sub> <sub>ms</sub> | <sub>0.0615</sub> <sub>ms</sub> | <sub>0.0563</sub> <sub>ms</sub> | <sub>0.0392</sub> <sub>ms</sub> | <sub>0.0060</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.1747</sub> <sub>ms</sub> | <sub>0.1232</sub> <sub>ms</sub> | <sub>0.1127</sub> <sub>ms</sub> | <sub>0.1003</sub> <sub>ms</sub> | <sub>0.0130</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.3473</sub> <sub>ms</sub> | <sub>0.2462</sub> <sub>ms</sub> | <sub>0.2249</sub> <sub>ms</sub> | <sub>0.1615</sub> <sub>ms</sub> | <sub>0.0309</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.5270</sub> <sub>ms</sub> | <sub>0.3680</sub> <sub>ms</sub> | <sub>0.3400</sub> <sub>ms</sub> | <sub>0.2644</sub> <sub>ms</sub> | <sub>0.0372</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>0.7034</sub> <sub>ms</sub> | <sub>0.4933</sub> <sub>ms</sub> | <sub>0.4506</sub> <sub>ms</sub> | <sub>0.3236</sub> <sub>ms</sub> | <sub>0.0612</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>0.8788</sub> <sub>ms</sub> | <sub>0.6157</sub> <sub>ms</sub> | <sub>0.5655</sub> <sub>ms</sub> | <sub>0.4042</sub> <sub>ms</sub> | <sub>0.0615</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>1.0556</sub> <sub>ms</sub> | <sub>0.7394</sub> <sub>ms</sub> | <sub>0.6822</sub> <sub>ms</sub> | <sub>0.4695</sub> <sub>ms</sub> | <sub>0.0803</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>1.2259</sub> <sub>ms</sub> | <sub>0.8674</sub> <sub>ms</sub> | <sub>0.7901</sub> <sub>ms</sub> | <sub>0.5680</sub> <sub>ms</sub> | <sub>0.0863</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>1.4111</sub> <sub>ms</sub> | <sub>0.9915</sub> <sub>ms</sub> | <sub>0.9080</sub> <sub>ms</sub> | <sub>0.6272</sub> <sub>ms</sub> | <sub>0.0987</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>1.5936</sub> <sub>ms</sub> | <sub>1.1236</sub> <sub>ms</sub> | <sub>1.0259</sub> <sub>ms</sub> | <sub>0.7032</sub> <sub>ms</sub> | <sub>0.1113</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>1.7681</sub> <sub>ms</sub> | <sub>1.2458</sub> <sub>ms</sub> | <sub>1.1467</sub> <sub>ms</sub> | <sub>0.8092</sub> <sub>ms</sub> | <sub>0.1376</sub> <sub>ms</sub> |


<sub>##</sub> <sub>Timings</sub> <sub>get_random</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0236</sub> <sub>ms</sub> | <sub>0.0195</sub> <sub>ms</sub> | <sub>0.0160</sub> <sub>ms</sub> | <sub>0.0124</sub> <sub>ms</sub> | <sub>0.0058</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.1376</sub> <sub>ms</sub> | <sub>0.1147</sub> <sub>ms</sub> | <sub>0.0881</sub> <sub>ms</sub> | <sub>0.0520</sub> <sub>ms</sub> | <sub>0.0416</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.3123</sub> <sub>ms</sub> | <sub>0.2636</sub> <sub>ms</sub> | <sub>0.1992</sub> <sub>ms</sub> | <sub>0.1330</sub> <sub>ms</sub> | <sub>0.0850</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.6780</sub> <sub>ms</sub> | <sub>0.5707</sub> <sub>ms</sub> | <sub>0.4108</sub> <sub>ms</sub> | <sub>0.2198</sub> <sub>ms</sub> | <sub>0.1865</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.9832</sub> <sub>ms</sub> | <sub>0.8007</sub> <sub>ms</sub> | <sub>0.7320</sub> <sub>ms</sub> | <sub>0.4012</sub> <sub>ms</sub> | <sub>0.5124</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>1.4257</sub> <sub>ms</sub> | <sub>1.1956</sub> <sub>ms</sub> | <sub>0.8668</sub> <sub>ms</sub> | <sub>0.5237</sub> <sub>ms</sub> | <sub>0.3870</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>1.9464</sub> <sub>ms</sub> | <sub>1.4823</sub> <sub>ms</sub> | <sub>1.2629</sub> <sub>ms</sub> | <sub>0.7642</sub> <sub>ms</sub> | <sub>0.7591</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>2.3951</sub> <sub>ms</sub> | <sub>2.0492</sub> <sub>ms</sub> | <sub>1.9207</sub> <sub>ms</sub> | <sub>0.9234</sub> <sub>ms</sub> | <sub>1.1135</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>3.3078</sub> <sub>ms</sub> | <sub>2.7856</sub> <sub>ms</sub> | <sub>2.6562</sub> <sub>ms</sub> | <sub>1.7146</sub> <sub>ms</sub> | <sub>0.5577</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>4.1680</sub> <sub>ms</sub> | <sub>3.6216</sub> <sub>ms</sub> | <sub>3.0702</sub> <sub>ms</sub> | <sub>1.9598</sub> <sub>ms</sub> | <sub>0.7960</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>5.5843</sub> <sub>ms</sub> | <sub>5.3055</sub> <sub>ms</sub> | <sub>4.2287</sub> <sub>ms</sub> | <sub>2.2099</sub> <sub>ms</sub> | <sub>1.1508</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>7.4481</sub> <sub>ms</sub> | <sub>5.7785</sub> <sub>ms</sub> | <sub>5.2061</sub> <sub>ms</sub> | <sub>2.6329</sub> <sub>ms</sub> | <sub>1.5942</sub> <sub>ms</sub> |


<sub>##</sub> <sub>Timings</sub> <sub>erase_sequential</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1122</sub> <sub>ms</sub> | <sub>0.0926</sub> <sub>ms</sub> | <sub>0.0712</sub> <sub>ms</sub> | <sub>0.0130</sub> <sub>ms</sub> | <sub>0.0077</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.5697</sub> <sub>ms</sub> | <sub>0.4856</sub> <sub>ms</sub> | <sub>0.4452</sub> <sub>ms</sub> | <sub>0.0569</sub> <sub>ms</sub> | <sub>0.0716</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.1702</sub> <sub>ms</sub> | <sub>0.9924</sub> <sub>ms</sub> | <sub>0.7436</sub> <sub>ms</sub> | <sub>0.1199</sub> <sub>ms</sub> | <sub>0.1565</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.4125</sub> <sub>ms</sub> | <sub>2.0546</sub> <sub>ms</sub> | <sub>1.5162</sub> <sub>ms</sub> | <sub>0.2473</sub> <sub>ms</sub> | <sub>0.3423</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>3.5992</sub> <sub>ms</sub> | <sub>3.0751</sub> <sub>ms</sub> | <sub>2.4073</sub> <sub>ms</sub> | <sub>0.4487</sub> <sub>ms</sub> | <sub>0.9524</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.4343</sub> <sub>ms</sub> | <sub>4.6499</sub> <sub>ms</sub> | <sub>3.6018</sub> <sub>ms</sub> | <sub>0.5973</sub> <sub>ms</sub> | <sub>0.7173</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>6.8324</sub> <sub>ms</sub> | <sub>5.9798</sub> <sub>ms</sub> | <sub>4.2246</sub> <sub>ms</sub> | <sub>0.7840</sub> <sub>ms</sub> | <sub>1.0936</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>8.5161</sub> <sub>ms</sub> | <sub>7.2317</sub> <sub>ms</sub> | <sub>5.5892</sub> <sub>ms</sub> | <sub>1.0377</sub> <sub>ms</sub> | <sub>1.9694</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>10.5874</sub> <sub>ms</sub> | <sub>8.2577</sub> <sub>ms</sub> | <sub>7.6498</sub> <sub>ms</sub> | <sub>2.1319</sub> <sub>ms</sub> | <sub>1.2071</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>11.8359</sub> <sub>ms</sub> | <sub>10.0899</sub> <sub>ms</sub> | <sub>8.1629</sub> <sub>ms</sub> | <sub>2.3336</sub> <sub>ms</sub> | <sub>1.4986</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>14.2806</sub> <sub>ms</sub> | <sub>13.1914</sub> <sub>ms</sub> | <sub>10.5865</sub> <sub>ms</sub> | <sub>2.7609</sub> <sub>ms</sub> | <sub>1.8171</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>17.9818</sub> <sub>ms</sub> | <sub>15.3503</sub> <sub>ms</sub> | <sub>11.9242</sub> <sub>ms</sub> | <sub>3.1052</sub> <sub>ms</sub> | <sub>2.3274</sub> <sub>ms</sub> |


<sub>##</sub> <sub>Timings</sub> <sub>erase_random</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1220</sub> <sub>ms</sub> | <sub>0.1033</sub> <sub>ms</sub> | <sub>0.0827</sub> <sub>ms</sub> | <sub>0.0134</sub> <sub>ms</sub> | <sub>0.0125</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.6152</sub> <sub>ms</sub> | <sub>0.5732</sub> <sub>ms</sub> | <sub>0.4123</sub> <sub>ms</sub> | <sub>0.0582</sub> <sub>ms</sub> | <sub>0.0771</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.3161</sub> <sub>ms</sub> | <sub>1.1204</sub> <sub>ms</sub> | <sub>0.8656</sub> <sub>ms</sub> | <sub>0.1205</sub> <sub>ms</sub> | <sub>0.1604</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.7473</sub> <sub>ms</sub> | <sub>2.3679</sub> <sub>ms</sub> | <sub>1.7900</sub> <sub>ms</sub> | <sub>0.2476</sub> <sub>ms</sub> | <sub>0.3437</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.2174</sub> <sub>ms</sub> | <sub>3.5594</sub> <sub>ms</sub> | <sub>2.8049</sub> <sub>ms</sub> | <sub>0.4474</sub> <sub>ms</sub> | <sub>0.9434</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.9897</sub> <sub>ms</sub> | <sub>4.9489</sub> <sub>ms</sub> | <sub>3.7988</sub> <sub>ms</sub> | <sub>0.5746</sub> <sub>ms</sub> | <sub>0.7137</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>7.5084</sub> <sub>ms</sub> | <sub>6.5011</sub> <sub>ms</sub> | <sub>5.6157</sub> <sub>ms</sub> | <sub>0.7775</sub> <sub>ms</sub> | <sub>1.0878</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>10.0182</sub> <sub>ms</sub> | <sub>8.9756</sub> <sub>ms</sub> | <sub>7.1233</sub> <sub>ms</sub> | <sub>1.0069</sub> <sub>ms</sub> | <sub>1.9498</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>13.0065</sub> <sub>ms</sub> | <sub>10.2430</sub> <sub>ms</sub> | <sub>8.8377</sub> <sub>ms</sub> | <sub>2.0786</sub> <sub>ms</sub> | <sub>1.1771</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>16.1498</sub> <sub>ms</sub> | <sub>13.2578</sub> <sub>ms</sub> | <sub>11.2337</sub> <sub>ms</sub> | <sub>2.2580</sub> <sub>ms</sub> | <sub>1.4762</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>19.8489</sub> <sub>ms</sub> | <sub>17.6300</sub> <sub>ms</sub> | <sub>13.8976</sub> <sub>ms</sub> | <sub>2.5950</sub> <sub>ms</sub> | <sub>1.8152</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>21.8800</sub> <sub>ms</sub> | <sub>23.1004</sub> <sub>ms</sub> | <sub>16.9499</sub> <sub>ms</sub> | <sub>2.8911</sub> <sub>ms</sub> | <sub>2.2601</sub> <sub>ms</sub> |


<sub>##</sub> <sub>Timings</sub> <sub>iterator</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.0035</sub> <sub>ms</sub> | <sub>0.0022</sub> <sub>ms</sub> | <sub>0.0078</sub> <sub>ms</sub> | <sub>0.0074</sub> <sub>ms</sub> | <sub>0.0024</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.0201</sub> <sub>ms</sub> | <sub>0.0219</sub> <sub>ms</sub> | <sub>0.0429</sub> <sub>ms</sub> | <sub>0.0531</sub> <sub>ms</sub> | <sub>0.0215</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>0.0506</sub> <sub>ms</sub> | <sub>0.0570</sub> <sub>ms</sub> | <sub>0.0901</sub> <sub>ms</sub> | <sub>0.1059</sub> <sub>ms</sub> | <sub>0.0508</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>0.1322</sub> <sub>ms</sub> | <sub>0.1316</sub> <sub>ms</sub> | <sub>0.1901</sub> <sub>ms</sub> | <sub>0.2117</sub> <sub>ms</sub> | <sub>0.1058</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>0.2266</sub> <sub>ms</sub> | <sub>0.2246</sub> <sub>ms</sub> | <sub>0.2540</sub> <sub>ms</sub> | <sub>0.2592</sub> <sub>ms</sub> | <sub>0.0457</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>0.3033</sub> <sub>ms</sub> | <sub>0.2989</sub> <sub>ms</sub> | <sub>0.3876</sub> <sub>ms</sub> | <sub>0.4328</sub> <sub>ms</sub> | <sub>0.2125</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>0.3889</sub> <sub>ms</sub> | <sub>0.4170</sub> <sub>ms</sub> | <sub>0.4804</sub> <sub>ms</sub> | <sub>0.4921</sub> <sub>ms</sub> | <sub>0.1596</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>0.5358</sub> <sub>ms</sub> | <sub>0.5290</sub> <sub>ms</sub> | <sub>0.6169</sub> <sub>ms</sub> | <sub>0.5276</sub> <sub>ms</sub> | <sub>0.0940</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>0.7319</sub> <sub>ms</sub> | <sub>0.7092</sub> <sub>ms</sub> | <sub>0.8605</sub> <sub>ms</sub> | <sub>0.8764</sub> <sub>ms</sub> | <sub>0.4561</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>1.0046</sub> <sub>ms</sub> | <sub>1.0206</sub> <sub>ms</sub> | <sub>0.9907</sub> <sub>ms</sub> | <sub>0.9436</sub> <sub>ms</sub> | <sub>0.4289</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>1.4750</sub> <sub>ms</sub> | <sub>1.4875</sub> <sub>ms</sub> | <sub>1.1981</sub> <sub>ms</sub> | <sub>1.0073</sub> <sub>ms</sub> | <sub>0.3869</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>1.8040</sub> <sub>ms</sub> | <sub>2.3138</sub> <sub>ms</sub> | <sub>1.4043</sub> <sub>ms</sub> | <sub>1.0595</sub> <sub>ms</sub> | <sub>0.3429</sub> <sub>ms</sub> |


<sub>##</sub> <sub>Timings</sub> <sub>create_insert_sum</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>0.1780</sub> <sub>ms</sub> | <sub>0.1351</sub> <sub>ms</sub> | <sub>0.1331</sub> <sub>ms</sub> | <sub>0.0198</sub> <sub>ms</sub> | <sub>0.0143</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>0.6929</sub> <sub>ms</sub> | <sub>0.6569</sub> <sub>ms</sub> | <sub>0.7850</sub> <sub>ms</sub> | <sub>0.1077</sub> <sub>ms</sub> | <sub>0.0697</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>1.3739</sub> <sub>ms</sub> | <sub>1.3106</sub> <sub>ms</sub> | <sub>1.2829</sub> <sub>ms</sub> | <sub>0.2143</sub> <sub>ms</sub> | <sub>0.1259</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>2.8851</sub> <sub>ms</sub> | <sub>2.6351</sub> <sub>ms</sub> | <sub>2.5324</sub> <sub>ms</sub> | <sub>0.5309</sub> <sub>ms</sub> | <sub>0.2607</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>4.2589</sub> <sub>ms</sub> | <sub>4.1533</sub> <sub>ms</sub> | <sub>3.7252</sub> <sub>ms</sub> | <sub>0.7280</sub> <sub>ms</sub> | <sub>0.3440</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>5.6199</sub> <sub>ms</sub> | <sub>5.5101</sub> <sub>ms</sub> | <sub>5.3512</sub> <sub>ms</sub> | <sub>1.0612</sub> <sub>ms</sub> | <sub>0.6157</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>6.9681</sub> <sub>ms</sub> | <sub>7.0093</sub> <sub>ms</sub> | <sub>6.9447</sub> <sub>ms</sub> | <sub>1.0156</sub> <sub>ms</sub> | <sub>0.5423</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>8.7625</sub> <sub>ms</sub> | <sub>8.3725</sub> <sub>ms</sub> | <sub>8.2368</sub> <sub>ms</sub> | <sub>1.4560</sub> <sub>ms</sub> | <sub>0.6983</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>10.2582</sub> <sub>ms</sub> | <sub>9.8201</sub> <sub>ms</sub> | <sub>10.1586</sub> <sub>ms</sub> | <sub>1.6024</sub> <sub>ms</sub> | <sub>1.0374</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>11.6925</sub> <sub>ms</sub> | <sub>10.9191</sub> <sub>ms</sub> | <sub>10.9802</sub> <sub>ms</sub> | <sub>1.7938</sub> <sub>ms</sub> | <sub>1.0596</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>12.9285</sub> <sub>ms</sub> | <sub>12.4082</sub> <sub>ms</sub> | <sub>13.0875</sub> <sub>ms</sub> | <sub>1.9500</sub> <sub>ms</sub> | <sub>1.0929</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>15.0190</sub> <sub>ms</sub> | <sub>15.0586</sub> <sub>ms</sub> | <sub>16.1472</sub> <sub>ms</sub> | <sub>2.0991</sub> <sub>ms</sub> | <sub>1.1236</sub> <sub>ms</sub> |


<sub>##</sub> <sub>Timings</sub> <sub>adds_and_removes</sub>

| <sub>counts</sub> | <sub>std::unordered_map</sub> | <sub>boost::unordered_map</sub> | <sub>eastl::hash_map</sub> | <sub>google::dense_hash_map</sub> | <sub>jc::hashtable</sub> |
|-------:|--------------------|----------------------|-----------------|------------------------|---------------|
| <sub>1000</sub> | <sub>1.1109</sub> <sub>ms</sub> | <sub>0.8341</sub> <sub>ms</sub> | <sub>0.8623</sub> <sub>ms</sub> | <sub>0.4252</sub> <sub>ms</sub> | <sub>0.3391</sub> <sub>ms</sub> |
| <sub>5000</sub> | <sub>4.3537</sub> <sub>ms</sub> | <sub>3.7974</sub> <sub>ms</sub> | <sub>3.0792</sub> <sub>ms</sub> | <sub>2.1627</sub> <sub>ms</sub> | <sub>1.6298</sub> <sub>ms</sub> |
| <sub>10000</sub> | <sub>9.4555</sub> <sub>ms</sub> | <sub>8.4022</sub> <sub>ms</sub> | <sub>6.7460</sub> <sub>ms</sub> | <sub>4.5051</sub> <sub>ms</sub> | <sub>3.4718</sub> <sub>ms</sub> |
| <sub>20000</sub> | <sub>23.3557</sub> <sub>ms</sub> | <sub>21.0842</sub> <sub>ms</sub> | <sub>16.3146</sub> <sub>ms</sub> | <sub>10.9390</sub> <sub>ms</sub> | <sub>8.9433</sub> <sub>ms</sub> |
| <sub>30000</sub> | <sub>36.3281</sub> <sub>ms</sub> | <sub>30.4519</sub> <sub>ms</sub> | <sub>26.0673</sub> <sub>ms</sub> | <sub>14.1808</sub> <sub>ms</sub> | <sub>16.3180</sub> <sub>ms</sub> |
| <sub>40000</sub> | <sub>52.5394</sub> <sub>ms</sub> | <sub>48.2025</sub> <sub>ms</sub> | <sub>36.9924</sub> <sub>ms</sub> | <sub>23.9023</sub> <sub>ms</sub> | <sub>19.4952</sub> <sub>ms</sub> |
| <sub>50000</sub> | <sub>71.7170</sub> <sub>ms</sub> | <sub>54.7715</sub> <sub>ms</sub> | <sub>47.6627</sub> <sub>ms</sub> | <sub>30.8231</sub> <sub>ms</sub> | <sub>27.4913</sub> <sub>ms</sub> |
| <sub>60000</sub> | <sub>78.1762</sub> <sub>ms</sub> | <sub>75.0088</sub> <sub>ms</sub> | <sub>60.7514</sub> <sub>ms</sub> | <sub>31.6031</sub> <sub>ms</sub> | <sub>36.5947</sub> <sub>ms</sub> |
| <sub>70000</sub> | <sub>106.6616</sub> <sub>ms</sub> | <sub>93.6189</sub> <sub>ms</sub> | <sub>75.8708</sub> <sub>ms</sub> | <sub>42.8003</sub> <sub>ms</sub> | <sub>32.5700</sub> <sub>ms</sub> |
| <sub>80000</sub> | <sub>159.6786</sub> <sub>ms</sub> | <sub>133.7742</sub> <sub>ms</sub> | <sub>114.7344</sub> <sub>ms</sub> | <sub>71.6712</sub> <sub>ms</sub> | <sub>42.7955</sub> <sub>ms</sub> |
| <sub>90000</sub> | <sub>161.1460</sub> <sub>ms</sub> | <sub>141.6574</sub> <sub>ms</sub> | <sub>113.6505</sub> <sub>ms</sub> | <sub>81.9605</sub> <sub>ms</sub> | <sub>45.4730</sub> <sub>ms</sub> |
| <sub>100000</sub> | <sub>229.5011</sub> <sub>ms</sub> | <sub>218.5141</sub> <sub>ms</sub> | <sub>159.0008</sub> <sub>ms</sub> | <sub>93.2573</sub> <sub>ms</sub> | <sub>59.1703</sub> <sub>ms</sub> |


