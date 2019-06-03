#include "ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>
/*
//t_int_str binpow2(int pwr);
static int *multiply(int *a, int *b, int size_a, int size_b)
{
	int *res;
	int size;
	int dif;
    int i;
    int j;

	size = size_a + size_b;
	res = (int *)malloc(sizeof(int) * size);
	ft_bzero(res, sizeof(int) * size);
    i = 0;
    while (i < size_a)
    {
        j = 0;
        while (j < size_b)
        {
            res[1 + i + j] += a[i] * b[j];
            ++j;
        }
        ++i;
    }
	while (size)
	{
		--size;
		if (res[size] > 9)
		{
			res[size - 1] += res[size] / 10;
			res[size] %= 10;
		}
	}
	return (res);
}

static void binpow2(int power)
{
	int *res;
	int *a;
	int *tmp;
	int size_res;
	int size_a;

	res = (int *)malloc(sizeof(int));
	a = (int *)malloc(sizeof(int));
	*res = 1;
	*a = (power < 0 ? 5 : 2);
	if (power < 0)
		power = ~power + 1;
	size_res = 1;
	size_a = 1;
	while (power)
	{
		if (power & 1)
		{
			tmp = res;
			res = multiply(res, a, size_res, size_a);
			free(tmp);
			size_res += size_a;
		}
		tmp = a;
		a = multiply(a, a, size_a, size_a);
		free(tmp);
		size_a *= 2;
		power >>= 1;
	}
	return (res);
}*/

int main()
{
long double d = 12345645612345612345612345612345612345612345612345612345612345612345612345612345612477584552641833114404193342158579965921211573280110014710625259622273859553694702927073204168102949538790614582405719458292053849054371167823367663833149082176223166974114799638943869122691886678627833405619236497104810698797391851990865865684964535509688038574474576597357892069374019208587069382232248633730302406280490311581017890911104054122429865047948274033970974076097466286613248068504413817433607984312676799562013955844479910057678934596780145013593792384007638892884775867536925725352469617147499810247290340163822722109043451120878057500652255270596955800988618351997972444377085657750293332548486577236894316145704036176702246315916567223748563512595228659466782646910400973591333574194540805191208881628298753134098500062727964100733146972369916883764370923323895714813987918116399062692351588707669363793398709373886160464585200464262369529675588208117864511972739440640524603888123456123456123456124775845526418331144041933421585799659212115732801100147106252596222738595536947029270732041681029495387906145824057194582920538490543711678233676638331490821762231669741147996389438691226918866786278334056192364971048106987973918519908658656849645355096880385744745765973578920693740192085870693822322486337303024062804903115810178909111040541224298650479482740339709740760974662866132480685044138174336079843126767995620139558444799100576789345967801450135937923840076388928847758675369257253524696171474998102472903401638227221090434511208780575006522552705969558009886183519979724443770856577502933325484865772368943161457040361767022463159165672237485635125952286594667826469104009735913335741945408051912088816282987531340985000627279641007331469723699168837643709233238957148139879181163990626923515887076693637933987093738861604645852004642623695296755882081178645119727394406405246038886261324088107767134016199311914135567039142840296306170625177010831360123456123456123456124775845526418331144041933421585799659212115732801100147106252596222738595536947029270732041681029495387906145824057194582920538490543711678233676638331490821762231669741147996389438691226918866786278334056192364971048106987973918519908658656849645355096880385744745765973578920693740192085870693822322486337303024062804903115810178909111040541224298650479482740339709740760974662866132480685044138174336079843126767995620139558444799100576789345967801450135937923840076388928847758675369257253524696171474998102472903401638227221090434511208780575006522552705969558009886183519979724443770856577502933325484865772368943161457040361767022463159165672237485635125952286594667826469104009735913335741945408051912088816282987531340985000627279641007331469723699168837643709233238957148139879181163990626923515887076693637933987093738861604645852004642623695296755882081178645119727394406405241234561234561234561247758455264183311440419334215857996592121157328011001471062525962227385955369470292707320416810294953879061458240571945829205384905437116782336766383314908217622316697411479963894386912269188667862783340561923649710481069879739185199086586568496453550968803857447457659735789206937401920858706938223224863373030240628049031158101789091110405412242986504794827403397097407609746628661324806850441381743360798431267679956201395584447991005767893459678014501359379238400763889288477586753692572535246961714749981024729034016382272210904345112087805750065225527059695580098861835199797244437708565775029333254848657723689431614570403617670224631591656722374856351259522865946678264691040097359133357419454080519120888162829875313409850006272796410073314697236991688376437092332389571481398791811639906269235158870766936379339870937388616046458520046426236952967558820811786451197273123456123456123456124775845526418331144041933421585799659212115732801100147106252596222738595536947029270732041681029495387906145824057194582920538490543711678233676638331490821762231669741147996389438691226918866786278334056192364971048106987973918519908658656849645355096880385744745765973578920693740192085870693822322486337303024062804903115810178909111040541224298650479482740339709740760974662866132480685044138174336079843126767995620139558444799100576789345967801450135937923840076388928847758675369257253524696171474998102472903401638227221090434511208780575006522552705969558009886183519979724443770856577502933325484865772368943161457040361767022463159165672237485635125952286594667826469104009735913335741945408051912088816282987531340985000627279641007331469723699168837643709233238957148139879181163990626923515887076693637933987093738861604645852004642623695296755882081178645119727324619931191413556703914284029630617062517701083136094406405246038886261324088107767134016199311914135567039142840296306170625177010831360603888626132408810776713401619931191413556703914284029630623456123456.123456L;
long double n = 0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000123412341234123423565L;
long double m = 1234345634567489527634958762398406501982365892734651089237556845632456234645687567845673456345656.0L;
long double z = 4123412.4576456754684568L;
//ft_printf("%.100Lf\n", n);
//printf("%.100Lf\n", n);
ft_printf("%Lf\n", d);
printf("%Lf\n", d);
}