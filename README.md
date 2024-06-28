# Numerically simulating percolation transition on a 2D regular lattice

The percolation process on a network can be considered as a physical problem involving a second-order phase transition. One can therefore apply the methods of statistical mechanics to explore the behaviour of such thermodynamical systems. Unfortunately, an analytic solution is not always found for this problem and it is therefore necessary to compute phase variables or critical properties via a simulation.

In this simulation, we explore the critical phenomena relative to a site-percolation transition on a 2D regular lattice

<img src="https://github.com/lorenzorizzi17/percolation_2d_grid/assets/102590961/eabf40e1-2f0f-47c1-ada1-b15748fc7ae9" alt="drawing" width="400" class="center"/>

### The phase transition
The phase transition appears around a certain _temperature_ $p_c$ (critical probability). Tracking the strength $S$ of the network (probability that a randomly chosen site belong to the percolating cluster) versus the probability $p$, one can quite easily see the sudden change in the macroscopical behaviour of the system


<img src="https://github.com/lorenzorizzi17/percolation_2d_grid/assets/102590961/b1956903-1ba4-4f78-886b-cfd9708bb1cd" alt="drawing" width="400"/>
<img src="https://github.com/lorenzorizzi17/percolation_2d_grid/assets/102590961/552367e8-94c0-4e48-b47b-ab69745f5704" alt="drawing" width="500"/>


## Estimating $p_c$, the critical probability at which the phase transition occurs
Using a technique known as _finite size analysis_, one can measure the critical point $p_c$ 


![Screenshot 2024-05-14 004311](https://github.com/lorenzorizzi17/percolation_2d_grid/assets/102590961/482ba119-f892-4f9b-8b0a-a4de74a2a503)


