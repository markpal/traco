from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d
from matplotlib.patches import Polygon
from numpy import *
import vis
import mpl_toolkits.mplot3d.art3d as art3d


class Arrow3D(FancyArrowPatch):
    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0,0), *args, **kwargs)
        self._verts3d = xs, ys, zs

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
        FancyArrowPatch.draw(self, renderer)


def imperf_vis(tilebises,dep):

    fig = plt.figure()
    ax = Axes3D(fig)
    colors = ['red', 'green', 'blue', 'yellow']

    tilex = -1
    tiley = -1
    tilept = []
    zs = []

    v=0



    for tilebis in tilebises:
        zs = [v]
        while(not tilebis.is_empty()):
            s = tilebis.lexmin()
            tilebis = tilebis.subtract(s)
            point =  s.sample_point()
            point = str(point)
            point = point.replace('[', '')
            point = point.replace(']', '')
            point = point.replace('{', '')
            point = point.replace('}', '')
            point = point.replace(' ', '')
            point = point.split(',')
            point = [int(i) for i in point]

            ax.scatter(point[2], v, point[3], 'ko', alpha=0.2)

            if((point[0] != tilex) or (point[1] != tiley)):
                if(len(tilept) > 0):
                    tilept = vis.convex_hull(tilept)
                    #ax.add_collection3d(PatchCollection([tilept], facecolors=[colors[v]]), zs = zs, zdir='y')
                    polygon = Polygon(tilept, True, facecolor=colors[v], alpha=0.4)
                    ax.add_patch(polygon)
                    art3d.pathpatch_2d_to_3d(polygon, z=v, zdir='y')

                    tilept = []
                    zs = [v]


                tilept.append((point[2],point[3]))
                tilex = point[0]
                tiley = point[1]
            else:
                tilept.append((point[2],point[3]))

        #draw the last
        if(len(tilept) > 0):
            tilept = vis.convex_hull(tilept)
            #ax.add_collection3d(PatchCollection([tilept], facecolors=[colors[v]]), zs=zs, zdir='y')
            polygon = Polygon(tilept, True, facecolor=colors[v], alpha=0.4)
            ax.add_patch(polygon)
            art3d.pathpatch_2d_to_3d(polygon, z=v, zdir='y')
            tilept=[]

        v = v + 1



    while(not dep.is_empty()):
        s = dep.sample()
        dep = dep.subtract(s)

        doms = s.domain()
        ranges = s.range()
        doms = doms.sample_point()
        ranges = ranges.sample_point()
        doms = vis.integer_list(doms)
        ranges = vis.integer_list(ranges)

        dv = 0
        rv = 0
        # to trzeba zautomatyzowac
        if doms[2] == 10:
            dv = 0
        else:
            dv = 1

        if ranges[2] == 10:
            rv = 0
        else:
            rv = 1
        # --------------------------

        a = Arrow3D([doms[0], ranges[0]], [dv, rv], [doms[1], ranges[1]], mutation_scale=10, lw=1, arrowstyle="-|>", color="k", alpha=0.4)
        ax.add_artist(a)

        ax.annotate("",
                xy=(ranges[0], ranges[1]), xycoords='data',
                xytext=(doms[0], doms[1]), textcoords='data',
                arrowprops=dict(arrowstyle="->",
                                connectionstyle="arc3"),
                )


    ax.set_xlim3d(-1,8)
    ax.set_ylim3d(0,1)
    ax.set_zlim3d(-1,8)

    plt.show()

