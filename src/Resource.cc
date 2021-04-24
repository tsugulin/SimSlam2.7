#include "Resource.h"
Define_Module(Resource);
#include "Lockup.h"

void Resource::initialize()
{
    // 変数を初期化
    owner = 0;   // 初期化

    // Awaitノードのポインタを取得
    cModule *mod = gate("from_await")->getPreviousGate()->getOwnerModule();
    node = check_and_cast<Lockup *>(mod);
}

// リソースの獲得を行う
bool Resource::request(long id)
{
    Enter_Method("request");
    bool ret_code = false;          // 戻り値を初期化
    if ( owner == 0 ) {
        owner = id;                 // もしリソースが未使用であれば要求者が利用可能とする
        displayArray(true);         // リソース使用中
        checkpoint = simTime();     // リソース獲得時刻を記録
        ret_code = true;            // リソース獲得に成功
    }
    return ret_code;    // リソース獲得できればtrueを戻す
}

// リソースの解放を行う
bool Resource::release(long id)
{
    Enter_Method("release");
    bool ret_code = false;          // 戻り値を初期化
    if ( owner == id ) {
        owner = 0;                  // リソースを解放
        displayArray(false);        // リソース未使用
        stats.collect( simTime() - checkpoint );    // リソース使用時間を記録
        node->goForward();     // 次のメッセージのリソースを確保する
        ret_code = true;            // リソース解放に成功
    }
    return ret_code;    // リソース解放できればtrueを戻す
}

// シミュレーション実行画面のアイコンに待ち状況を表示する
void Resource::displayArray(bool flag)
{
    if (flag)
        getDisplayString().setTagArg("t", 0, "Now Using");
    else
        getDisplayString().setTagArg("t", 0, "Now Available");
}

void Resource::finish()
{
    EV << "Resource jobs Count:  " << stats.getCount() << endl;
    EV << "Resource Utilization: " << stats.getSum() / simTime() << endl;
}
