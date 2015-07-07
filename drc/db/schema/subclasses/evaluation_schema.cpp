#include "evaluation_schema.h"

EvaluationSchema::EvaluationSchema() : DatabaseSchema()
{
    setTableName("Evaluation_Table");

    initializeHeaders();
    initializeColumnTypes();
}

#define OVERRIDES_OF_BASE {

void EvaluationSchema::initializeHeaders()
{
    QVector<QString> evaluationHeaders;

    evaluationHeaders.append("Id");
    evaluationHeaders.append("startDate");
    evaluationHeaders.append("endDate");
    evaluationHeaders.append("CountIdd");
    evaluationHeaders.append("FairYes");
    evaluationHeaders.append("FairNo");
    evaluationHeaders.append("FairSomewhat");
    evaluationHeaders.append("ImproveYes");
    evaluationHeaders.append("ImproveNo");
    evaluationHeaders.append("ImroveSomewhat");
    evaluationHeaders.append("CommunicateYes");
    evaluationHeaders.append("CommunicateNo");
    evaluationHeaders.append("CommunicateSomewhat");
    evaluationHeaders.append("UnderstandYes");
    evaluationHeaders.append("UnderstandNo");
    evaluationHeaders.append("UnderstandSomewhat");
    evaluationHeaders.append("RecommendYes");
    evaluationHeaders.append("RecommendNo");
    evaluationHeaders.append("RecommendSomewhat");
    evaluationHeaders.append("AgreementYes");
    evaluationHeaders.append("AgreementNo");
    evaluationHeaders.append("AgreementSomewhat");

    setHeader(evaluationHeaders);
}

void EvaluationSchema::initializeColumnTypes()
{
    QVector<RECORD_TYPE> evaluationColumnType;

    evaluationColumnType.append(PRIMARY_ID);
    evaluationColumnType.append(LOWER_DATE);
    evaluationColumnType.append(UPPER_DATE);
    evaluationColumnType.append(COUNTY);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);
    evaluationColumnType.append(EVALUATION_SCORE);

    setColumnType(evaluationColumnType);
}

#define OVERRIDES_OF_BASE }
