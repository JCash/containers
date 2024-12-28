# jc::Array benchmarks

Benchmarks run on a: b'MacBookPro18,3'   b'Apple M1 Pro'

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

| <sub>counts</sub> | <sub>carray</sub> | <sub>std::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> |
|--------:|-----------|-------------|---------------|-----------|
| <sub>100000</sub> | <sub>0.7136</sub> <sub>ms</sub> | <sub>0.7120</sub> <sub>ms</sub> | <sub>0.7120</sub> <sub>ms</sub> | <sub>0.7121</sub> <sub>ms</sub> |

| <sub>200000</sub> | <sub>1.4414</sub> <sub>ms</sub> | <sub>1.4360</sub> <sub>ms</sub> | <sub>1.4263</sub> <sub>ms</sub> | <sub>1.4266</sub> <sub>ms</sub> |

| <sub>300000</sub> | <sub>2.2113</sub> <sub>ms</sub> | <sub>2.2018</sub> <sub>ms</sub> | <sub>2.1843</sub> <sub>ms</sub> | <sub>2.2096</sub> <sub>ms</sub> |

| <sub>400000</sub> | <sub>3.0264</sub> <sub>ms</sub> | <sub>2.9470</sub> <sub>ms</sub> | <sub>2.9482</sub> <sub>ms</sub> | <sub>2.9983</sub> <sub>ms</sub> |

| <sub>500000</sub> | <sub>3.8195</sub> <sub>ms</sub> | <sub>3.7090</sub> <sub>ms</sub> | <sub>3.7188</sub> <sub>ms</sub> | <sub>3.7883</sub> <sub>ms</sub> |

| <sub>600000</sub> | <sub>4.6223</sub> <sub>ms</sub> | <sub>4.4828</sub> <sub>ms</sub> | <sub>4.4828</sub> <sub>ms</sub> | <sub>4.5829</sub> <sub>ms</sub> |

| <sub>700000</sub> | <sub>5.4262</sub> <sub>ms</sub> | <sub>5.2497</sub> <sub>ms</sub> | <sub>5.2559</sub> <sub>ms</sub> | <sub>5.3947</sub> <sub>ms</sub> |

| <sub>800000</sub> | <sub>6.2504</sub> <sub>ms</sub> | <sub>6.0370</sub> <sub>ms</sub> | <sub>6.0279</sub> <sub>ms</sub> | <sub>6.1950</sub> <sub>ms</sub> |

| <sub>900000</sub> | <sub>6.9080</sub> <sub>ms</sub> | <sub>6.8053</sub> <sub>ms</sub> | <sub>6.8157</sub> <sub>ms</sub> | <sub>6.9795</sub> <sub>ms</sub> |

| <sub>1000000</sub> | <sub>7.8038</sub> <sub>ms</sub> | <sub>7.5842</sub> <sub>ms</sub> | <sub>7.5914</sub> <sub>ms</sub> | <sub>7.7868</sub> <sub>ms</sub> |



## <sub>Timings</sub> <sub>get_random_large</sub>

| <sub>counts</sub> | <sub>carray</sub> | <sub>std::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> |
|--------:|------------|-------------|---------------|------------|
| <sub>100000</sub> | <sub>0.7189</sub> <sub>ms</sub> | <sub>0.7155</sub> <sub>ms</sub> | <sub>0.7153</sub> <sub>ms</sub> | <sub>0.7154</sub> <sub>ms</sub> |

| <sub>200000</sub> | <sub>1.8261</sub> <sub>ms</sub> | <sub>1.7670</sub> <sub>ms</sub> | <sub>2.0246</sub> <sub>ms</sub> | <sub>1.7935</sub> <sub>ms</sub> |

| <sub>300000</sub> | <sub>3.3612</sub> <sub>ms</sub> | <sub>3.3522</sub> <sub>ms</sub> | <sub>3.3595</sub> <sub>ms</sub> | <sub>3.3588</sub> <sub>ms</sub> |

| <sub>400000</sub> | <sub>4.8297</sub> <sub>ms</sub> | <sub>4.8163</sub> <sub>ms</sub> | <sub>4.8187</sub> <sub>ms</sub> | <sub>4.8242</sub> <sub>ms</sub> |

| <sub>500000</sub> | <sub>6.2771</sub> <sub>ms</sub> | <sub>6.2727</sub> <sub>ms</sub> | <sub>6.2831</sub> <sub>ms</sub> | <sub>6.2735</sub> <sub>ms</sub> |

| <sub>600000</sub> | <sub>7.7423</sub> <sub>ms</sub> | <sub>7.6815</sub> <sub>ms</sub> | <sub>7.6870</sub> <sub>ms</sub> | <sub>7.6786</sub> <sub>ms</sub> |

| <sub>700000</sub> | <sub>9.1008</sub> <sub>ms</sub> | <sub>9.0972</sub> <sub>ms</sub> | <sub>9.1050</sub> <sub>ms</sub> | <sub>9.0908</sub> <sub>ms</sub> |

| <sub>800000</sub> | <sub>10.4983</sub> <sub>ms</sub> | <sub>10.4903</sub> <sub>ms</sub> | <sub>10.4965</sub> <sub>ms</sub> | <sub>10.5044</sub> <sub>ms</sub> |

| <sub>900000</sub> | <sub>13.3733</sub> <sub>ms</sub> | <sub>11.8640</sub> <sub>ms</sub> | <sub>11.8804</sub> <sub>ms</sub> | <sub>11.8810</sub> <sub>ms</sub> |

| <sub>1000000</sub> | <sub>15.3142</sub> <sub>ms</sub> | <sub>13.2417</sub> <sub>ms</sub> | <sub>13.2668</sub> <sub>ms</sub> | <sub>13.2599</sub> <sub>ms</sub> |



## <sub>Timings</sub> <sub>sum</sub>

| <sub>counts</sub> | <sub>carray</sub> | <sub>std::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> |
|--------:|-----------|-------------|---------------|-----------|
| <sub>100000</sub> | <sub>0.0108</sub> <sub>ms</sub> | <sub>0.0104</sub> <sub>ms</sub> | <sub>0.0101</sub> <sub>ms</sub> | <sub>0.0100</sub> <sub>ms</sub> |

| <sub>200000</sub> | <sub>0.0230</sub> <sub>ms</sub> | <sub>0.0229</sub> <sub>ms</sub> | <sub>0.0228</sub> <sub>ms</sub> | <sub>0.0225</sub> <sub>ms</sub> |

| <sub>300000</sub> | <sub>0.0397</sub> <sub>ms</sub> | <sub>0.0376</sub> <sub>ms</sub> | <sub>0.0375</sub> <sub>ms</sub> | <sub>0.0368</sub> <sub>ms</sub> |

| <sub>400000</sub> | <sub>0.0558</sub> <sub>ms</sub> | <sub>0.0528</sub> <sub>ms</sub> | <sub>0.0528</sub> <sub>ms</sub> | <sub>0.0527</sub> <sub>ms</sub> |

| <sub>500000</sub> | <sub>0.0693</sub> <sub>ms</sub> | <sub>0.0676</sub> <sub>ms</sub> | <sub>0.0686</sub> <sub>ms</sub> | <sub>0.0676</sub> <sub>ms</sub> |

| <sub>600000</sub> | <sub>0.0852</sub> <sub>ms</sub> | <sub>0.0831</sub> <sub>ms</sub> | <sub>0.0835</sub> <sub>ms</sub> | <sub>0.0858</sub> <sub>ms</sub> |

| <sub>700000</sub> | <sub>0.1000</sub> <sub>ms</sub> | <sub>0.0983</sub> <sub>ms</sub> | <sub>0.0987</sub> <sub>ms</sub> | <sub>0.0993</sub> <sub>ms</sub> |

| <sub>800000</sub> | <sub>0.1545</sub> <sub>ms</sub> | <sub>0.1141</sub> <sub>ms</sub> | <sub>0.1143</sub> <sub>ms</sub> | <sub>0.1130</sub> <sub>ms</sub> |

| <sub>900000</sub> | <sub>0.1812</sub> <sub>ms</sub> | <sub>0.1295</sub> <sub>ms</sub> | <sub>0.1288</sub> <sub>ms</sub> | <sub>0.1269</sub> <sub>ms</sub> |

| <sub>1000000</sub> | <sub>0.2667</sub> <sub>ms</sub> | <sub>0.1455</sub> <sub>ms</sub> | <sub>0.1455</sub> <sub>ms</sub> | <sub>0.1403</sub> <sub>ms</sub> |



## <sub>Timings</sub> <sub>push_back</sub>

| <sub>counts</sub> | <sub>carray</sub> | <sub>std::vector</sub> | <sub>boost::vector</sub> | <sub>jc::Array</sub> |
|--------:|-----------|-------------|---------------|-----------|
| <sub>100000</sub> | <sub>0.0635</sub> <sub>ms</sub> | <sub>0.0506</sub> <sub>ms</sub> | <sub>0.2146</sub> <sub>ms</sub> | <sub>0.0378</sub> <sub>ms</sub> |

| <sub>200000</sub> | <sub>0.1305</sub> <sub>ms</sub> | <sub>0.1007</sub> <sub>ms</sub> | <sub>0.4294</sub> <sub>ms</sub> | <sub>0.0757</sub> <sub>ms</sub> |

| <sub>300000</sub> | <sub>0.2014</sub> <sub>ms</sub> | <sub>0.1511</sub> <sub>ms</sub> | <sub>0.6551</sub> <sub>ms</sub> | <sub>0.1135</sub> <sub>ms</sub> |

| <sub>400000</sub> | <sub>0.0991</sub> <sub>ms</sub> | <sub>0.2017</sub> <sub>ms</sub> | <sub>0.8755</sub> <sub>ms</sub> | <sub>0.1506</sub> <sub>ms</sub> |

| <sub>500000</sub> | <sub>0.2848</sub> <sub>ms</sub> | <sub>0.2520</sub> <sub>ms</sub> | <sub>1.0953</sub> <sub>ms</sub> | <sub>0.1885</sub> <sub>ms</sub> |

| <sub>600000</sub> | <sub>0.3390</sub> <sub>ms</sub> | <sub>0.3025</sub> <sub>ms</sub> | <sub>1.3008</sub> <sub>ms</sub> | <sub>0.2253</sub> <sub>ms</sub> |

| <sub>700000</sub> | <sub>0.1089</sub> <sub>ms</sub> | <sub>0.3529</sub> <sub>ms</sub> | <sub>1.5326</sub> <sub>ms</sub> | <sub>0.2647</sub> <sub>ms</sub> |

| <sub>800000</sub> | <sub>0.4559</sub> <sub>ms</sub> | <sub>0.4036</sub> <sub>ms</sub> | <sub>1.7343</sub> <sub>ms</sub> | <sub>0.3016</sub> <sub>ms</sub> |

| <sub>900000</sub> | <sub>0.5053</sub> <sub>ms</sub> | <sub>0.4539</sub> <sub>ms</sub> | <sub>1.9627</sub> <sub>ms</sub> | <sub>0.3415</sub> <sub>ms</sub> |

| <sub>1000000</sub> | <sub>0.5665</sub> <sub>ms</sub> | <sub>0.5072</sub> <sub>ms</sub> | <sub>2.1670</sub> <sub>ms</sub> | <sub>0.3783</sub> <sub>ms</sub> |



