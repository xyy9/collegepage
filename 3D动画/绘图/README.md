### Lab1：

> 操作說明：

```
(只使用OpenGL中畫點的功能)
功能1-畫點：按下‘d’鍵，在畫布上用滑鼠左鍵畫點，滑鼠按下的時候點生成。
功能2-畫線：按下‘l’鍵，在畫布上用滑鼠左鍵拖動畫線，滑鼠按下的坐標為起始點，抬起的坐標為終止點，連成一直線。
                  （注意：不是滑鼠按兩下，多邊形的畫線用的才是那個0.0）
功能3-畫多邊形：按下‘p’鍵，在畫布上用滑鼠左鍵畫線，點擊一下為一個坐標，會與上一個坐標連城線，點右鍵會將多邊形封閉。
功能4-畫圓：按下‘o’鍵，在畫布上用滑鼠左鍵選擇圓心，拖動滑鼠送開的位置與圓心組成半徑。
                  （我讓圓心也畫在畫面上了，這樣看起來比較好看是否正確~，如果不需要註解掉代碼裡面第142行就好）
功能5-清除：按下‘c’鍵，畫布會變回白色的，如果需要繼續畫畫，要按上面的鍵之後才行。
功能6-恢復：按下‘r’鍵，會將從執行開始所有畫過的東西重現。
功能7-結束程式：按下‘q’鍵，畫布視窗就會不見了，over！
```


### Lab2：

> 操作說明：

```
glut視窗設定: 寬(x)->800  高(y)->600
程式按下enter後會顯示已進行的步驟，只有印黃色的規定圖案，而白色的view邊窗沒有印出
```

> 測資說明：

```
在Debug資料夾下
有A~E五個測資
執行：2019CG_Lab2_106502601.exe inputfile.in
```

> 指令說明：

```
1.scale: x y
2.rotate: degree
3.translate: x y
4.square
5.triangle
6.view: wxl wxr wyb wyt vxl vxr vyb vyt
7.clearData
8.clearScreen
9.reset
10.end
11.# command(註解)
```


### Lab3：

> code說明：

```
除了.in的指令之外，每次object的指令結束後會印出對應的TM的矩陣，更改observer後會印Tilt, Mirror, GRM, TE的矩陣，每次viewport後會印視窗的範圍（xmin,xmax,ymin,ymax）和windows_to_view的矩陣，每次display後會印最終的PM和EM矩陣。
```

> 測資說明：

```
在Debug資料夾下
有A~E五個測資
執行：2019CG_Lab3_106502601.exe inputfile.in
```

> 指令說明：

```
1.scale: x y z
2.rotate: x y z
3.translate: x y z
4.object: object.asc
5.observer: Ex Ey Ez COIx COIy COIz Tilt Hither Yon Hav
6.viewport: vxl vxr vyb vyt (即Vxmin Vxmax Vymin Vymax)
7.display
8.nobackfaces
9.Reset 對Transformation Matrix做初始化
10.end
11.# command(註解)
```


### Lab4：

> code說明：

```
用zbuffer alg.來上色，display之後以面為單位上色。
刷新zbuffer的方法是，以面為單位取一個正方形方框，然後判斷方框裡面每一個點是否在面的polygon中，如果在就判斷zbuffer然後刷新colorbuffer
```

> 測資說明：

```
在Debug資料夾下
有A~D四個測資
執行：2019CG_Lab4_106502601.exe inputfile.in
```

> 指令說明：

```
1.scale: x y z
2.rotate: x y z
3.translate: x y z
4.observer: Ex Ey Ez COIx COIy COIz Tilt Hither Yon Hav
5.viewport: vxl vxr vyb vyt (即Vxmin Vxmax Vymin Vymax)
6.display
7.reset 對Transformation Matrix做初始化
8. end
9 .# command(註解)
8.object: object.asc Or Og Ob Kd Ks N
9.ambient: KaIar KaIag KaIab
10.background: Br Bg Bb
11.light: index Ipr Ipg Ipb Ix Iy Iz
```


### Lab5：

> code說明：

```
用判断两线是否有交点的方式求xa,xb然后通过跟polygon中每个x的比例来算每个pixel的rgb（polygon的每个顶点的平均法向量存为一个array）
```

> 測資說明：

```
在Debug資料夾下
執行：2019CG_Lab5_106502601.exe inputfile.in
```